.text
.globl main
main:
    jal ra, drawBackground
    li a0, 10 
    ecall
drawBackground:
    addi sp, sp, -16
    sw ra, 4(sp)
    sw ra, 12(sp)
    sw s0, 8(sp)
    sw s1, 4(sp)
    sw s2, 0(sp)
 
    li s0, 31
    li s1, 29 
    li s2, 0
    li s3, 0
  
    loop1:
        li s0, 31 
      
        loop2:
            add a0, s3, s0
            add a1, s3, s2
            jal ra, lightLED
            addi s0, s0, -1  # Increment s0 instead of decrementing
            bge s0, s3, loop2
        addi s2, s2, 1
        ble s2, s1, loop1
    li t3, 30
    lw ra, 12(sp)
    lw s0, 8(sp)
    lw s1, 4(sp)
    lw s2, 0(sp)
    addi sp, sp, 16 
    ret
lightLED:

    addi sp, sp, -12
    sw ra, 8(sp) 
    sw t0, 4(sp)
    add t0, s3, a0 
    add t1, s3, a1 

    jal ra, lightColor
    mv t3, a0 

    add a2, x0, a0
    li a0, 0x100
    li a1, 0x00000000
    slli a1, t0, 16 
    add a1, a1, t1 
    ecall
    lw ra, 8(sp)
    addi sp, sp, 12
    ret
lightColor:
    
    addi t4, s3, 4         
    la t2, grid           
   
    mul t5, t1, t4         
    addi t4, s3, 31

    sub t4, t4, t0  
    add t2, t2, t5  
   
    lw t3, 0(t2)      
    srl t3, t3, t4         
    
    andi t6, t3, 1      
    beqz t6, gold  
    li a0, 0xBA0C2F     
    j return            
    gold:     
        li a0, 0xA89968
    return:            
    ret  
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