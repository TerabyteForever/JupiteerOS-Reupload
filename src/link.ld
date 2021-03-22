ENTRY(loader)

. = 0x00100000;

kernel_start = .;

SECTIONS{

  .boot ALIGN (0x1000):{
    *(.multiboot_header)
  }

  .text ALIGN (0x1000):{
    *(.text)
  }

  .rodata ALIGN (0x1000):{
    *(.rodaata*)
  }

  .data ALIGN (0x1000):{
    *(.data)
  }

  .bss ALIGN (0x1000):{
    *(COMMON)
    *(.bss)
  }

}

end = .;