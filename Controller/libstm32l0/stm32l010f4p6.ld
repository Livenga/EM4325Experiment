MEMORY {
  FLASH (rx): ORIGIN = 0x08000000, LENGTH = 16K,
  SRAM(xrw):  ORIGIN = 0x20000000, LENGTH = 2K
}

ENTRY(Reset_handler)

_estack = ORIGIN(SRAM) + LENGTH(SRAM);
min_heap_size  = 0x0000;
min_stack_size = 0x0200;


SECTIONS {
  . = 0x00000000;

  .irq_vector : {
    . = ALIGN(4);
    KEEP(*(.vector))
    . = ALIGN(4);
  } > FLASH

  .text : {
    . = ALIGN(4);
    __text_start__ = .;

    *(.text)
    *(.text*)
    *(.rodata)
    *(.rodata*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)

    KEEP(*(.init))
    KEEP(*(.fini))

    . = ALIGN(4);
    _etext = .;
    __text_end__ = .;
  } > FLASH

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
  .ARM : {
    __exidx_start = .;
      *(.ARM.exidx*)
      __exidx_end = .;
  } >FLASH

  .preinit_array : {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH

  .init_array : {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH

  .fini_array : {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  _sidata = .;

  .data : AT(_sidata) {
    . = ALIGN(4);

    _sdata = .;
    __data_start__ = .;
    *(.data)
    *(.data*)

    . = ALIGN(4);
    _edata = .;
    __data_end__ = .;
  } > SRAM

  .bss : {
    . = ALIGN(4);
    _sbss = .;
    __bss_start__ = .;

    *(.bss)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = .;
  } > SRAM

  ._user_heap_stack : {
    . = ALIGN(4);
    PROVIDE(end = .);
    PROVIDE(_end = .);
    . = . + min_heap_size;
    . = . + min_stack_size;
    . = ALIGN(4);
  } > SRAM

  /DISCARD/ : {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
