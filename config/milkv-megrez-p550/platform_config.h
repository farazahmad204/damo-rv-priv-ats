/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Milk-V Megrez (ESWIN EIC7700X, SiFive P550) platform configuration.
 * Values match the ACT-Runner board milkv_megrez_eic7700x, which loads and
 * starts the test ELFs on this board.
 */
#ifndef PLATFORM_MILKV_MEGREZ_P550_H
#define PLATFORM_MILKV_MEGREZ_P550_H

/* This header is included via CFLAGS -include for C code only.
 * Assembly-only constants are in rvmodel_macros.h (included via ASFLAGS). */

/* ===== UART0: DesignWare 8250, 4-byte register stride, 16-bit accesses ===== */
#define PLATFORM_UART0_BASE      0x50900000UL
#define PLATFORM_UART_TYPE       0          /* NS16550 */
#define PLATFORM_UART_REG_SHIFT  2
#define PLATFORM_UART_IO_WIDTH   2
/* 115200 baud from the 200 MHz UART clock: (200000000 + 8 * 115200) / (16 * 115200) */
#define UART_DLL_VALUE           109
#define UART_DLM_VALUE           0

/* ===== Memory: the runner's payload window ===== */
#ifndef PLATFORM_MEM_BASE
#define PLATFORM_MEM_BASE        0x90000000UL
#endif
#define PLATFORM_MEM_SIZE        0x20000000UL    /* 512 MB, up to 0xB0000000 */

#define CONFIG_NAME              "Milk-V Megrez (SiFive P550)"

/* ===== CLINT: tests run on hart 1, so use hart 1's MSIP / MTIMECMP ===== */
#define PLATFORM_CLINT_BASE      0x02000000UL
#define CLINT_SUPPORTED
#define MSWI_SUPPORTED
#define PLATFORM_BOOT_HARTID     1
#define PLATFORM_MSIP_ADDR       (PLATFORM_CLINT_BASE + 4UL * PLATFORM_BOOT_HARTID)
#define PLATFORM_MTIMECMP_ADDR   (PLATFORM_CLINT_BASE + 0x4000UL + 8UL * PLATFORM_BOOT_HARTID)
#define PLATFORM_MTIME_ADDR      (PLATFORM_CLINT_BASE + 0xBFF8UL)   /* 1 MHz */

#endif /* PLATFORM_MILKV_MEGREZ_P550_H */
