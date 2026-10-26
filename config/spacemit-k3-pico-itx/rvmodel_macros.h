/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * SpacemiT K3 Pico-ITX (SpacemiT X100): DUT macros.
 *
 * The UART runner (ACT-Runner, board spacemit_k3_pico_itx) starts the ELF in
 * M-mode on hart 0. The K3 has no monitor hart polling tohost: the runner ends
 * the case on the M-mode ecall below and reads tohost (1 = PASS, 3 = FAIL).
 */
#ifndef _RVMODEL_MACROS_H
#define _RVMODEL_MACROS_H

#define RVMODEL_DATA_SECTION \
        .pushsection .tohost,"aw",@progbits;                \
        .align 8; .global tohost; tohost: .dword 0;         \
        .align 8; .global fromhost; fromhost: .dword 0;     \
        .popsection

#define STANDARD_SM_SUPPORTED

/* The runner starts the ELF on hart 0. */
#define RVMODEL_BOOT_HARTID 0

/* Turn on H: misa.H is writable and resets to 0 on the X100. */
#define RVMODEL_BOOT \
  csrr t1, misa                  ;\
  ori  t1, t1, 0x80              ;\
  csrw misa, t1                  ;\
  csrw 0x645, zero  /* hvip */

/* ===== TERMINATION: tohost, then an M-mode ecall into the runner =====
 * common/entry.S saved the runner's mtvec (rvtest_entry_mtvec) before installing
 * its own handler; restore it so the ecall reaches the runner. */
#define RVMODEL_HALT_PASS  \
  la   t0, tohost                ;\
  li   t1, 1                     ;\
  sd   t1, 0(t0)                 ;\
  la   t0, rvtest_entry_mtvec    ;\
  ld   t0, 0(t0)                 ;\
  csrw mtvec, t0                 ;\
  fence rw, rw                   ;\
  ecall                          ;\
  halt_pass_loop:                ;\
    wfi                          ;\
    j halt_pass_loop             ;\

#define RVMODEL_HALT_FAIL \
  la   t0, tohost                ;\
  li   t1, 3                     ;\
  sd   t1, 0(t0)                 ;\
  la   t0, rvtest_entry_mtvec    ;\
  ld   t0, 0(t0)                 ;\
  csrw mtvec, t0                 ;\
  fence rw, rw                   ;\
  ecall                          ;\
  halt_fail_loop:                ;\
    wfi                          ;\
    j halt_fail_loop             ;\

#endif /* _RVMODEL_MACROS_H */
