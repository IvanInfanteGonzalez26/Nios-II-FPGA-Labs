/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_gen2_0' in SOPC Builder design 'Reloj_system'
 * SOPC Builder design path: ../../Reloj_system.sopcinfo
 *
 * Generated: Thu Jul 16 17:13:41 CDT 2026
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x00020820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x12
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00010020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x12
#define ALT_CPU_NAME "nios2_gen2_0"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00010000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00020820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x12
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00010020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x12
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00010000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone V"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/null"
#define ALT_STDERR_BASE 0x0
#define ALT_STDERR_DEV null
#define ALT_STDERR_TYPE ""
#define ALT_STDIN "/dev/null"
#define ALT_STDIN_BASE 0x0
#define ALT_STDIN_DEV null
#define ALT_STDIN_TYPE ""
#define ALT_STDOUT "/dev/null"
#define ALT_STDOUT_BASE 0x0
#define ALT_STDOUT_DEV null
#define ALT_STDOUT_TYPE ""
#define ALT_SYSTEM_NAME "Reloj_system"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER_0
#define ALT_TIMESTAMP_CLK none


/*
 * onchip_memory2_0 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2_0 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_0_BASE 0x10000
#define ONCHIP_MEMORY2_0_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_0_DUAL_PORT 0
#define ONCHIP_MEMORY2_0_GUI_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_INIT_CONTENTS_FILE "Reloj_system_onchip_memory2_0"
#define ONCHIP_MEMORY2_0_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_0_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_0_IRQ -1
#define ONCHIP_MEMORY2_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_0_NAME "/dev/onchip_memory2_0"
#define ONCHIP_MEMORY2_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_0_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_0_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY2_0_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_0_SIZE_VALUE 65536
#define ONCHIP_MEMORY2_0_SPAN 65536
#define ONCHIP_MEMORY2_0_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_0_WRITABLE 1


/*
 * pio_1_hex configuration
 *
 */

#define ALT_MODULE_CLASS_pio_1_hex altera_avalon_pio
#define PIO_1_HEX_BASE 0x210b0
#define PIO_1_HEX_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_1_HEX_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_1_HEX_CAPTURE 0
#define PIO_1_HEX_DATA_WIDTH 7
#define PIO_1_HEX_DO_TEST_BENCH_WIRING 0
#define PIO_1_HEX_DRIVEN_SIM_VALUE 0
#define PIO_1_HEX_EDGE_TYPE "NONE"
#define PIO_1_HEX_FREQ 50000000
#define PIO_1_HEX_HAS_IN 0
#define PIO_1_HEX_HAS_OUT 1
#define PIO_1_HEX_HAS_TRI 0
#define PIO_1_HEX_IRQ -1
#define PIO_1_HEX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_1_HEX_IRQ_TYPE "NONE"
#define PIO_1_HEX_NAME "/dev/pio_1_hex"
#define PIO_1_HEX_RESET_VALUE 0
#define PIO_1_HEX_SPAN 16
#define PIO_1_HEX_TYPE "altera_avalon_pio"


/*
 * pio_2_hex configuration
 *
 */

#define ALT_MODULE_CLASS_pio_2_hex altera_avalon_pio
#define PIO_2_HEX_BASE 0x210a0
#define PIO_2_HEX_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_2_HEX_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_2_HEX_CAPTURE 0
#define PIO_2_HEX_DATA_WIDTH 7
#define PIO_2_HEX_DO_TEST_BENCH_WIRING 0
#define PIO_2_HEX_DRIVEN_SIM_VALUE 0
#define PIO_2_HEX_EDGE_TYPE "NONE"
#define PIO_2_HEX_FREQ 50000000
#define PIO_2_HEX_HAS_IN 0
#define PIO_2_HEX_HAS_OUT 1
#define PIO_2_HEX_HAS_TRI 0
#define PIO_2_HEX_IRQ -1
#define PIO_2_HEX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_2_HEX_IRQ_TYPE "NONE"
#define PIO_2_HEX_NAME "/dev/pio_2_hex"
#define PIO_2_HEX_RESET_VALUE 0
#define PIO_2_HEX_SPAN 16
#define PIO_2_HEX_TYPE "altera_avalon_pio"


/*
 * pio_3_hex configuration
 *
 */

#define ALT_MODULE_CLASS_pio_3_hex altera_avalon_pio
#define PIO_3_HEX_BASE 0x21090
#define PIO_3_HEX_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_3_HEX_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_3_HEX_CAPTURE 0
#define PIO_3_HEX_DATA_WIDTH 7
#define PIO_3_HEX_DO_TEST_BENCH_WIRING 0
#define PIO_3_HEX_DRIVEN_SIM_VALUE 0
#define PIO_3_HEX_EDGE_TYPE "NONE"
#define PIO_3_HEX_FREQ 50000000
#define PIO_3_HEX_HAS_IN 0
#define PIO_3_HEX_HAS_OUT 1
#define PIO_3_HEX_HAS_TRI 0
#define PIO_3_HEX_IRQ -1
#define PIO_3_HEX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_3_HEX_IRQ_TYPE "NONE"
#define PIO_3_HEX_NAME "/dev/pio_3_hex"
#define PIO_3_HEX_RESET_VALUE 0
#define PIO_3_HEX_SPAN 16
#define PIO_3_HEX_TYPE "altera_avalon_pio"


/*
 * pio_4_hex configuration
 *
 */

#define ALT_MODULE_CLASS_pio_4_hex altera_avalon_pio
#define PIO_4_HEX_BASE 0x21080
#define PIO_4_HEX_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_4_HEX_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_4_HEX_CAPTURE 0
#define PIO_4_HEX_DATA_WIDTH 7
#define PIO_4_HEX_DO_TEST_BENCH_WIRING 0
#define PIO_4_HEX_DRIVEN_SIM_VALUE 0
#define PIO_4_HEX_EDGE_TYPE "NONE"
#define PIO_4_HEX_FREQ 50000000
#define PIO_4_HEX_HAS_IN 0
#define PIO_4_HEX_HAS_OUT 1
#define PIO_4_HEX_HAS_TRI 0
#define PIO_4_HEX_IRQ -1
#define PIO_4_HEX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_4_HEX_IRQ_TYPE "NONE"
#define PIO_4_HEX_NAME "/dev/pio_4_hex"
#define PIO_4_HEX_RESET_VALUE 0
#define PIO_4_HEX_SPAN 16
#define PIO_4_HEX_TYPE "altera_avalon_pio"


/*
 * pio_botones configuration
 *
 */

#define ALT_MODULE_CLASS_pio_botones altera_avalon_pio
#define PIO_BOTONES_BASE 0x21070
#define PIO_BOTONES_BIT_CLEARING_EDGE_REGISTER 0
#define PIO_BOTONES_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PIO_BOTONES_CAPTURE 0
#define PIO_BOTONES_DATA_WIDTH 3
#define PIO_BOTONES_DO_TEST_BENCH_WIRING 0
#define PIO_BOTONES_DRIVEN_SIM_VALUE 0
#define PIO_BOTONES_EDGE_TYPE "NONE"
#define PIO_BOTONES_FREQ 50000000
#define PIO_BOTONES_HAS_IN 1
#define PIO_BOTONES_HAS_OUT 0
#define PIO_BOTONES_HAS_TRI 0
#define PIO_BOTONES_IRQ -1
#define PIO_BOTONES_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIO_BOTONES_IRQ_TYPE "NONE"
#define PIO_BOTONES_NAME "/dev/pio_botones"
#define PIO_BOTONES_RESET_VALUE 0
#define PIO_BOTONES_SPAN 16
#define PIO_BOTONES_TYPE "altera_avalon_pio"


/*
 * timer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer
#define TIMER_0_ALWAYS_RUN 0
#define TIMER_0_BASE 0x21000
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_FIXED_PERIOD 0
#define TIMER_0_FREQ 50000000
#define TIMER_0_IRQ 0
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_LOAD_VALUE 49999
#define TIMER_0_MULT 0.001
#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_PERIOD 1
#define TIMER_0_PERIOD_UNITS "ms"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_SNAPSHOT 1
#define TIMER_0_SPAN 32
#define TIMER_0_TICKS_PER_SEC 1000
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
