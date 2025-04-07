.text
main:
  li x18, 0x100
  li x19, 0
  la x20, grid
row_loop:
  lw x21, 0(x20)
  li x22, 0          # Start from the first bit

bit_loop:
  sll x23, x21, x22
  slli x24, x22, 16
  or x25, x24, x19

  li x26, 0xBA0C2F
  bltz x23, set_led
  li x26, 0xA89968
  j set_led

set_led:
  mv a0, x18
  mv a1, x25
  mv a2, x26
  ecall

  addi x22, x22, 1    # Move to the next bit
  li x27, 32          # Number of bits in a word
  blt x22, x27, bit_loop

  addi x19, x19, 1
  addi x20, x20, 4
  li x12, 31
  blt x19, x12, row_loop

  li x10, 10  # Exit syscall
  ecall

.data
grid:
  .word 0xFFFFFC00
  .word 0xFFFFFE00
  .word 0xFFFFFF00
  .word 0x3FFFFF00

  .word 0x3F003F00
  .word 0x3F003F00
  .word 0x3F3F3F3F
  .word 0x3F3F3F3F

  .word 0x3F3F3F3F
  .word 0x3F3F3F3F
  .word 0x3F3F3F3F
  .word 0x3F3F3F3F

  .word 0x3F3F3F3F
  .word 0x3F3F3F3F
  .word 0x3F3F3F3F
  .word 0x3F3F3F3F

  .word 0x3F3F3F3F
  .word 0x3F3F3F3F
  .word 0x3F003F3F
  .word 0x3F003F3F

  .word 0x3FFFFF3F
  .word 0xFFFFFF3F
  .word 0xFFFFFE3F
  .word 0xFFFFFC3F

  .word 0x0000007F
  .word 0x000000FF
  .word 0x003FFFFF
  .word 0x003FFFFF

  .word 0x001FFFFE
  .word 0x000FFFFC