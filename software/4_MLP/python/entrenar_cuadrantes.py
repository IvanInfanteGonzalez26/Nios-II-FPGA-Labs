"""Entrena y exporta un MLP float32 con el simpleclass dataset.

Red: 2 entradas -> 10 neuronas ReLU -> 4 salidas.

Requisito:
    python -m pip install numpy

Antes de ejecutarlo, generar simpleclass.csv desde MATLAB con:
    run('exportar_simpleclass.m')

Ejecucion:
    python entrenar_cuadrantes.py
"""

from pathlib import Path

import numpy as np


SEMILLA = 17
EPOCAS = 750
TASA_APRENDIZAJE = 0.08
ESCALA = 256
NEURONAS_OCULTAS = 10


def cargar_simpleclass() -> tuple[np.ndarray, np.ndarray]:
    ruta = Path(__file__).with_name("simpleclass.csv")
    if not ruta.is_file():
        raise FileNotFoundError(
            "Falta simpleclass.csv. Abra MATLAB con Deep Learning Toolbox y "
            "ejecute exportar_simpleclass.m antes de entrenar."
        )

    datos = np.loadtxt(ruta, delimiter=",")
    if datos.shape != (1000, 3):
        raise ValueError(
            f"Se esperaba simpleclass.csv con forma (1000, 3), no {datos.shape}."
        )

    entradas = datos[:, :2].astype(np.float64)
    etiquetas = datos[:, 2].astype(np.int64)
    if not np.all((etiquetas >= 0) & (etiquetas < 4)):
        raise ValueError("Las clases de simpleclass.csv deben estar entre 0 y 3.")

    conteos = np.bincount(etiquetas, minlength=4)
    print(f"Muestras simpleclass por clase: {conteos.tolist()}")
    return entradas, etiquetas


def relu(valores: np.ndarray) -> np.ndarray:
    return np.maximum(valores, 0.0)


def inferir(
    entradas: np.ndarray,
    w1: np.ndarray,
    b1: np.ndarray,
    w2: np.ndarray,
    b2: np.ndarray,
) -> np.ndarray:
    oculta = relu(entradas @ w1 + b1)
    return oculta @ w2 + b2


def entrenar(
    entradas: np.ndarray, etiquetas: np.ndarray, rng: np.random.Generator
) -> tuple[np.ndarray, np.ndarray, np.ndarray, np.ndarray]:
    cantidad = entradas.shape[0]
    w1 = rng.normal(0.0, 0.5, size=(2, NEURONAS_OCULTAS))
    b1 = np.zeros(NEURONAS_OCULTAS)
    w2 = rng.normal(0.0, 0.5, size=(NEURONAS_OCULTAS, 4))
    b2 = np.zeros(4)

    objetivo = np.eye(4)[etiquetas]

    for epoca in range(EPOCAS):
        z1 = entradas @ w1 + b1
        a1 = relu(z1)
        logits = a1 @ w2 + b2

        logits_estables = logits - logits.max(axis=1, keepdims=True)
        probabilidades = np.exp(logits_estables)
        probabilidades /= probabilidades.sum(axis=1, keepdims=True)

        dlogits = (probabilidades - objetivo) / cantidad
        dw2 = a1.T @ dlogits
        db2 = dlogits.sum(axis=0)
        da1 = dlogits @ w2.T
        dz1 = da1 * (z1 > 0)
        dw1 = entradas.T @ dz1
        db1 = dz1.sum(axis=0)

        w1 -= TASA_APRENDIZAJE * dw1
        b1 -= TASA_APRENDIZAJE * db1
        w2 -= TASA_APRENDIZAJE * dw2
        b2 -= TASA_APRENDIZAJE * db2

        if epoca % 250 == 0 or epoca == EPOCAS - 1:
            prediccion = logits.argmax(axis=1)
            precision = np.mean(prediccion == etiquetas)
            print(f"Epoca {epoca:4d}: precision={precision:.4f}")

    return w1, b1, w2, b2


def cuantizar(valores: np.ndarray, tipo: type[np.signedinteger]) -> np.ndarray:
    return np.rint(valores * ESCALA).astype(tipo)


def inferir_entero(
    entradas_q: np.ndarray,
    w1_q: np.ndarray,
    b1_q: np.ndarray,
    w2_q: np.ndarray,
    b2_q: np.ndarray,
) -> np.ndarray:
    """Replica las operaciones de punto fijo que ejecutara Nios II."""
    acumulador_1 = entradas_q.astype(np.int64) @ w1_q.astype(np.int64)
    acumulador_1 += b1_q.astype(np.int64) * ESCALA
    oculta_q = np.maximum(acumulador_1 >> 8, 0)

    acumulador_2 = oculta_q @ w2_q.astype(np.int64)
    acumulador_2 += b2_q.astype(np.int64) * ESCALA
    return acumulador_2 >> 8


def matriz_c(nombre: str, valores: np.ndarray, tipo_c: str) -> str:
    filas = []
    for fila in valores:
        filas.append("    { " + ", ".join(str(int(v)) for v in fila) + " }")
    contenido = ",\n".join(filas)
    dimensiones = "".join(f"[{dimension}]" for dimension in valores.shape)
    return f"static const {tipo_c} {nombre}{dimensiones} = {{\n{contenido}\n}};"


def vector_c(nombre: str, valores: np.ndarray, tipo_c: str) -> str:
    contenido = ", ".join(str(int(v)) for v in valores)
    return f"static const {tipo_c} {nombre}[{len(valores)}] = {{ {contenido} }};"


def matriz_float_c(nombre: str, valores: np.ndarray) -> str:
    filas = []
    for fila in valores:
        elementos = ", ".join(f"{float(v):.9g}f" for v in fila)
        filas.append("    { " + elementos + " }")
    contenido = ",\n".join(filas)
    dimensiones = "".join(f"[{dimension}]" for dimension in valores.shape)
    return f"static const float {nombre}{dimensiones} = {{\n{contenido}\n}};"


def vector_float_c(nombre: str, valores: np.ndarray) -> str:
    contenido = ", ".join(f"{float(v):.9g}f" for v in valores)
    return f"static const float {nombre}[{len(valores)}] = {{ {contenido} }};"


def exportar_header_q8(
    ruta: Path,
    w1_q: np.ndarray,
    b1_q: np.ndarray,
    w2_q: np.ndarray,
    b2_q: np.ndarray,
) -> None:
    # C usa pesos[neurona_destino][entrada], por eso se transponen.
    texto = "\n\n".join(
        [
            """#ifndef MLP_WEIGHTS_H
#define MLP_WEIGHTS_H

#include <stdint.h>

#define MLP_INPUTS 2
#define MLP_HIDDEN 10
#define MLP_OUTPUTS 4
#define MLP_SHIFT 8
#define MLP_SCALE (1 << MLP_SHIFT)""",
            matriz_c("mlp_w1", w1_q.T, "int16_t"),
            vector_c("mlp_b1", b1_q, "int32_t"),
            matriz_c("mlp_w2", w2_q.T, "int16_t"),
            vector_c("mlp_b2", b2_q, "int32_t"),
            "#endif /* MLP_WEIGHTS_H */\n",
        ]
    )
    ruta.write_text(texto, encoding="utf-8")


def exportar_header_float(
    ruta: Path,
    w1: np.ndarray,
    b1: np.ndarray,
    w2: np.ndarray,
    b2: np.ndarray,
) -> None:
    # Se fuerza float32 y se transpone al orden [destino][origen] usado en C.
    texto = "\n\n".join(
        [
            """#ifndef MLP_WEIGHTS_FLOAT_H
#define MLP_WEIGHTS_FLOAT_H

#define MLP_INPUTS 2
#define MLP_HIDDEN 10
#define MLP_OUTPUTS 4""",
            matriz_float_c("mlp_w1", w1.astype(np.float32).T),
            vector_float_c("mlp_b1", b1.astype(np.float32)),
            matriz_float_c("mlp_w2", w2.astype(np.float32).T),
            vector_float_c("mlp_b2", b2.astype(np.float32)),
            "#endif /* MLP_WEIGHTS_FLOAT_H */\n",
        ]
    )
    ruta.write_text(texto, encoding="utf-8")


def main() -> None:
    rng = np.random.default_rng(SEMILLA)
    entradas, etiquetas = cargar_simpleclass()

    indices = rng.permutation(len(entradas))
    corte = int(0.8 * len(indices))
    entrenamiento = indices[:corte]
    prueba = indices[corte:]

    w1, b1, w2, b2 = entrenar(
        entradas[entrenamiento], etiquetas[entrenamiento], rng
    )

    pred_float = inferir(entradas[prueba], w1, b1, w2, b2).argmax(axis=1)

    entradas_q = cuantizar(entradas[prueba], np.int16)
    w1_q = cuantizar(w1, np.int16)
    b1_q = cuantizar(b1, np.int32)
    w2_q = cuantizar(w2, np.int16)
    b2_q = cuantizar(b2, np.int32)
    salidas_q = inferir_entero(entradas_q, w1_q, b1_q, w2_q, b2_q)
    pred_q = salidas_q.argmax(axis=1)

    print(f"Precision flotante de prueba:   {np.mean(pred_float == etiquetas[prueba]):.4f}")
    print(f"Precision cuantizada de prueba: {np.mean(pred_q == etiquetas[prueba]):.4f}")
    print(f"Coincidencia float/Q8:           {np.mean(pred_float == pred_q):.4f}")

    salida_float = Path(__file__).with_name("mlp_weights_float.h")
    exportar_header_float(salida_float, w1, b1, w2, b2)
    print(f"Pesos float32 exportados en: {salida_float}")

    salida_nios = (
        Path(__file__).resolve().parent.parent
        / "software"
        / "Ej4_mlp_sw"
        / "mlp_weights_float.h"
    )
    if salida_nios.parent.is_dir():
        exportar_header_float(salida_nios, w1, b1, w2, b2)
        print(f"Pesos float32 copiados para Nios II en: {salida_nios}")

    salida_q8 = Path(__file__).with_name("mlp_weights_q8.h")
    exportar_header_q8(salida_q8, w1_q, b1_q, w2_q, b2_q)
    print(f"Pesos Q8 de referencia en: {salida_q8}")


if __name__ == "__main__":
    main()
