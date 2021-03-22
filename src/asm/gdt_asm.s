; Allows the C code to call gdt_flush()
global gdt_flush

gdt_flush:
  ; Fetch pointer to GDT and pass it as a parameter
  mov eax, [esp + 4]
  ; Load the new GDT pointer
  lgdt [eax]

  ; Data segment size 16 bytes.So,it's offset is 0x10.
  mov ax, 0x10

  ; Load all data segment registers
  mov ds, ax         
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  ; Each gdt entry is 8 bytes.So,it's offset is 0x08.
  ; Do far jump
  jmp 0x08: .flush

.flush:
  ret