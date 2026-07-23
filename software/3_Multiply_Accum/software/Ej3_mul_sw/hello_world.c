#include <stdio.h>
#include "system.h"
#include "alt_types.h"
#include "altera_avalon_performance_counter.h"

#define SECCION_CODIGO 1

int main()
{
		int vector_1[100], vector_2[100];
		int i = 0, mul_acum = 0;

		//llenar vectores
		for(i = 0; i < 100; i++)
		{
			vector_1[i] = i + 1;
			vector_2[i] = i + 1;
		}

		// 1. Resetear todos los contadores a cero
	    PERF_RESET(PERFORMANCE_COUNTER_0_BASE);

	    // 2. ACTIVAR EL CONTADOR GLOBAL (Indispensable para que el hardware cuente)
	    PERF_START_MEASURING(PERFORMANCE_COUNTER_0_BASE);

	    // 3. Delimitar la secci n espec fica que quieres medir (Secci n 1)
	    PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECCION_CODIGO);
	    for(i = 0; i < 100; i++)
	    {
	    	mul_acum += vector_1[i]* vector_2[i];
	    }

	  // 4. Terminar la secci n espec fica
	    PERF_END(PERFORMANCE_COUNTER_0_BASE, SECCION_CODIGO);

	    // 5. Detener el contador global
	    PERF_STOP_MEASURING(PERFORMANCE_COUNTER_0_BASE);


	    // 6. Obtener los resultados de la Secci n 1
	    alt_u64 ticks = perf_get_section_time(PERFORMANCE_COUNTER_0_BASE, SECCION_CODIGO);

	    // Calcular el tiempo en segundos
	    double tiempo_seg = (double)ticks / ALT_CPU_FREQ;

	    printf("Ciclos de reloj: %llu\n", ticks);
	    printf("Tiempo de ejecuci n: %f segundos\n", tiempo_seg);

	    return 0;
}
