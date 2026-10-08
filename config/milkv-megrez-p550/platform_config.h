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

/* ===== CSRs the P550 does not implement (privileged 1.11, H draft 0.6) =====
 * csr_probe on the board: these raise illegal instruction. The shared reset
 * code assumes priv 1.12+, so the M-mode trap handler emulates them as
 * read-zero / write-ignored when a test has not armed the trap.
 *   0x30a menvcfg, 0x10a senvcfg, 0x60a henvcfg, 0x605 htimedelta,
 *   0x14d stimecmp, 0x24d vstimecmp (no Sstc) */
#define PLATFORM_ABSENT_CSRS     0x30a, 0x10a, 0x60a, 0x605, 0x14d, 0x24d

#endif /* PLATFORM_MILKV_MEGREZ_P550_H */
