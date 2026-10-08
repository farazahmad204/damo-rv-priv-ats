# Milk-V Megrez (ESWIN EIC7700X, SiFive P550) on real hardware.
#
# There is no simulator: the ELF is sent over the UART to the minimal M-mode
# runner that replaces OpenSBI in the board's boot chain (ACT-Runner,
# board milkv_megrez_eic7700x). The runner loads the ELF, starts it in M-mode
# on hart 1 and reports PASS/FAIL from the tohost write of
# RVMODEL_HALT_PASS/FAIL.

# Cross compiler
CROSS_COMPILER ?= riscv64-unknown-elf-

# The runner accepts ELFs linked inside its payload window 0x90000000-0xB0000000.
MEM_BASE ?= 0x90000000
