/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * SpacemiT K3 Pico-ITX (SpacemiT X100) platform configuration.
 * Values match the ACT-Runner board spacemit_k3_pico_itx, which loads and
 * starts the test ELFs on this board.
 */
#ifndef PLATFORM_SPACEMIT_K3_PICO_ITX_H
#define PLATFORM_SPACEMIT_K3_PICO_ITX_H

/* This header is included via CFLAGS -include for C code only.
 * Assembly-only constants are in rvmodel_macros.h (included via ASFLAGS). */

/* ===== UART0: 8250 (XScale/PXA), 4-byte register stride, byte accesses =====
 * The boot loader leaves it at 115200 baud and the runner prints through it. On this
 * UART IER bit 6 (UUE) enables the unit, so the standard init (IER = 0) would turn it
 * off: keep the firmware's setup and only transmit. */
#define PLATFORM_UART0_BASE      0xD4017000UL
#define PLATFORM_UART_TYPE       0          /* NS16550 */
#define PLATFORM_UART_REG_SHIFT  2
#define PLATFORM_UART_IO_WIDTH   1
#define PLATFORM_UART_KEEP_FIRMWARE_SETUP

/* ===== Memory: the runner's payload window ===== */
#ifndef PLATFORM_MEM_BASE
#define PLATFORM_MEM_BASE        0x110000000UL
#endif
#define PLATFORM_MEM_SIZE        0x20000000UL    /* 512 MB, up to 0x130000000 */

#define CONFIG_NAME              "SpacemiT K3 Pico-ITX (SpacemiT X100)"

/* ===== CLINT: tests run on hart 0 ===== */
#define PLATFORM_CLINT_BASE      0xF1810000UL
#define CLINT_SUPPORTED
#define MSWI_SUPPORTED
#define PLATFORM_BOOT_HARTID     0
#define PLATFORM_MSIP_ADDR       (PLATFORM_CLINT_BASE + 4UL * PLATFORM_BOOT_HARTID)
#define PLATFORM_MTIMECMP_ADDR   (PLATFORM_CLINT_BASE + 0x4000UL + 8UL * PLATFORM_BOOT_HARTID)
#define PLATFORM_MTIME_ADDR      (PLATFORM_CLINT_BASE + 0xBFF8UL)

#endif /* PLATFORM_SPACEMIT_K3_PICO_ITX_H */
