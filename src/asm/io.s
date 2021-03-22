global outb
global inb

; outb - send a byte to an I/O port
; stack: [esp + 8] the data byte
;	[esp + 4] the I/O port
; [esp]     return address

outb:
  ; move the data to be sent into the al register
  mov al, [esp + 8]
  ; move the address of the I/O port into the dx register
  mov dx, [esp + 4]
  ; send the data to the I/O port
  out dx, al
  ; return to the calling function
  ret

inb:
  ; move the address of the I/O port into the dx register
  mov dx, [esp + 4]
  ; take the data to the I/O port
  in al, dx
  ; return to the calling function
  ret