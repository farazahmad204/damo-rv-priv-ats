/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Milk-V Megrez (ESWIN EIC7700X, SiFive P550): DUT macros.
 *
 * The UART runner (ACT-Runner, board milkv_megrez_eic7700x) starts the ELF in
 * M-mode on hart 1 and reports the result from tohost: 1 = PASS, 3 = FAIL.
 */
#ifndef _RVMODEL_MACROS_H
#define _RVMODEL_MACROS_H

#define RVMODEL_DATA_SECTION \
        .pushsection .tohost,"aw",@progbits;                \
        .align 8; .global tohost; tohost: .dword 0;         \
        .align 8; .global fromhost; fromhost: .dword 0;     \
        .popsection

#define STANDARD_SM_SUPPORTED

/* The runner starts the ELF on hart 1 (common/entry.S lets this hart run). */
#define RVMODEL_BOOT_HARTID 1

/* hvip reads 0x440 at runner entry on this board (pending VS timer and VS
 * external interrupt bits left by earlier boot stages). Clear it so the H
 * tests start from a known state. */
#define RVMODEL_BOOT \
  csrw 0x645, zero  /* hvip */

/* ===== TERMINATION: tohost, polled by the runner ===== */
#define RVMODEL_HALT_PASS  \
  li x1, 1                ;\
  la t0, tohost           ;\
  write_tohost_pass:      ;\
    sw x1, 0(t0)          ;\
    sw x0, 4(t0)          ;\
    j write_tohost_pass   ;\

#define RVMODEL_HALT_FAIL \
  li x1, 3                ;\
  la t0, tohost           ;\
  write_tohost_fail:      ;\
    sw x1, 0(t0)          ;\
    sw x0, 4(t0)          ;\
    j write_tohost_fail   ;\

#endif /* _RVMODEL_MACROS_H */
