OUTPUT_ARCH( "riscv" )
ENTRY(rvtest_entry_point)

/* Milk-V Megrez: the UART runner loads ELFs inside 0x90000000-0xB0000000. */
SECTIONS
{
  . = 0x90000000;
  .text.init    : { *(.text.init) }
  .text.rvtest  : { *(.text.rvtest) *(.text.rvtest.*) }
  . = ALIGN(0x4000);
  .data         : { *(.data) }
  . = ALIGN(0x1000);
  .text.rvmodel : { *(.text.rvmodel) *(.text.rvmodel.*) *(.text) *(.text.*) }
  . = ALIGN(0x1000);
  _end = .;
}
