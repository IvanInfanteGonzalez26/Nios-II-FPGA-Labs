#include <stdio.h>
#include "system.h"
#include "alt_types.h"
#include "altera_avalon_performance_counter.h"
#include "mlp_weights_float.h"

#define SECCION_INFERENCIA 1
#define REPETICIONES 1000

static float relu(float valor)
{
    return valor > 0.0f ? valor : 0.0f;
}

static int mlp_predecir(const float entrada[MLP_INPUTS], float salida[MLP_OUTPUTS])
{
    float oculta[MLP_HIDDEN];
    int neurona;
    int origen;
    int clase = 0;

    for (neurona = 0; neurona < MLP_HIDDEN; ++neurona) {
        float acumulador = mlp_b1[neurona];

        for (origen = 0; origen < MLP_INPUTS; ++origen) {
            acumulador += entrada[origen] * mlp_w1[neurona][origen];
        }

        oculta[neurona] = relu(acumulador);
    }

    for (neurona = 0; neurona < MLP_OUTPUTS; ++neurona) {
        float acumulador = mlp_b2[neurona];

        for (origen = 0; origen < MLP_HIDDEN; ++origen) {
            acumulador += oculta[origen] * mlp_w2[neurona][origen];
        }

        salida[neurona] = acumulador;
    }

    for (neurona = 1; neurona < MLP_OUTPUTS; ++neurona) {
        if (salida[neurona] > salida[clase]) {
            clase = neurona;
        }
    }

    return clase;
}

int main(void)
{
    static const float puntos[][MLP_INPUTS] = {
        {  0.50f,  0.25f },
        { -0.50f,  0.75f },
        { -0.75f, -0.50f },
        {  0.25f, -0.75f }
    };
    float salida[MLP_OUTPUTS];
    volatile int suma_control = 0;
    alt_u64 ciclos;
    alt_u64 ciclos_promedio;
    alt_u64 tiempo_us;
    unsigned int muestra;
    unsigned int repeticion;

    printf("MLP float32: clasificador simpleclass\n");

    for (muestra = 0; muestra < sizeof(puntos) / sizeof(puntos[0]); ++muestra) {
        int clase = mlp_predecir(puntos[muestra], salida);

        printf(
            "Entrada (%f, %f) -> clase %d\n",
            (double)puntos[muestra][0],
            (double)puntos[muestra][1],
            clase
        );
    }

    PERF_RESET(PERFORMANCE_COUNTER_0_BASE);
    PERF_START_MEASURING(PERFORMANCE_COUNTER_0_BASE);
    PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECCION_INFERENCIA);

    for (repeticion = 0; repeticion < REPETICIONES; ++repeticion) {
        muestra = repeticion % (sizeof(puntos) / sizeof(puntos[0]));
        suma_control += mlp_predecir(puntos[muestra], salida);
    }

    PERF_END(PERFORMANCE_COUNTER_0_BASE, SECCION_INFERENCIA);
    PERF_STOP_MEASURING(PERFORMANCE_COUNTER_0_BASE);

    ciclos = perf_get_section_time(
        (void *)PERFORMANCE_COUNTER_0_BASE,
        SECCION_INFERENCIA
    );
    ciclos_promedio = ciclos / REPETICIONES;
    tiempo_us = (ciclos * 1000000ULL) / ALT_CPU_FREQ;

    printf("Inferencias medidas: %u\n", REPETICIONES);
    printf("Ciclos totales: %llu\n", ciclos);
    printf("Ciclos promedio por inferencia: %llu\n", ciclos_promedio);
    printf("Tiempo total: %llu us\n", tiempo_us);
    printf("Suma de control: %d\n", suma_control);

    return 0;
}
