.section .data
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

.section .text
.globl _start

_start:
    # Set LED matrix size
    li a0, 31  # x size
    li a1, 29  # y size
    li a7, 1027  # system call number for setting LED matrix size
    ecall

    # Set up loop counters
    li t0, 0    # y counter
    li t1, 0    # x counter

outer_loop:
    # Load address of grid[y] into t2
    la t2, grid
    add t2, t2, t0  # Move to the current row

inner_loop:
    # Load the current row into t3
    lw t3, 0(t2)

    # Extract the color bits for the current x position
    srl t4, t3, t1       # Shift the color bits to the rightmost position
    andi t4, t4, 0x1      # Mask to get the rightmost bit

    # Determine the color and set t5 accordingly
    beqz t4, set_gold      # If t4 is 0, set gold color
    li t5, 0xBA0C2F        # Crimson color (0xBA0C2F)
    j set_color

set_gold:
    li t5, 0xA89968        # Gold color (0xA89968)

set_color:
    # Set a0 to turn on LED
    li a0, 0x100

    # Calculate the LED position in a1
    slli t6, t0, 16       # Shift y to bits 31-16
    or t6, t6, t1        # Combine with x position

    # Set the LED color in a2
    mv a2, t5

    # Make the system call
    ecall

    # Increment x counter
    addi t1, t1, 1

    # Check if x counter has reached 32
    li t6, 32
    bne t1, t6, inner_loop

    # Reset x counter and increment y counter
    li t1, 0
    addi t0, t0, 1

    # Check if y counter has reached 30
    li t6, 30
    bne t0, t6, outer_loop

    # End program
    li a0, 10
    ecall