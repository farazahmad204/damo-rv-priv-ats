# SpacemiT K3 Pico-ITX (SpacemiT X100) on real hardware.
#
# There is no simulator: the ELF is sent over the UART to the minimal M-mode
# runner that replaces OpenSBI in the board's boot chain (ACT-Runner,
# board spacemit_k3_pico_itx). The runner loads the ELF, starts it in M-mode
# on hart 0 and ends the case on the M-mode ecall of RVMODEL_HALT_PASS/FAIL,
# reading PASS/FAIL from tohost.

# Cross compiler
CROSS_COMPILER ?= riscv64-unknown-elf-

# The runner accepts ELFs linked inside its payload window 0x110000000-0x130000000.
MEM_BASE ?= 0x110000000
