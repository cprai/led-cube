











.origin 0
.entrypoint START



.macro LD32
.mparam dst,src
    LBBO dst,src,#0x00,4
.endm

.macro LD16
.mparam dst,src
    LBBO dst,src,#0x00,2
.endm

.macro LD8
.mparam dst,src
    LBBO dst,src,#0x00,1
.endm

.macro ST32
.mparam src,dst
    SBBO src,dst,#0x00,4
.endm

.macro ST16
.mparam src,dst
    SBBO src,dst,#0x00,2
.endm

.macro ST8
.mparam src,dst
    SBBO src,dst,#0x00,1
.endm

.macro stack_init
    mov r0, (0x2000 - 0x200)
.endm

.macro push
.mparam reg, cnt
    sbbo reg, r0, 0, 4*cnt
    add r0, r0, 4*cnt
.endm

.macro pop
.mparam reg, cnt
    sub r0, r0, 4*cnt
    lbbo reg, r0, 0, 4*cnt
.endm

.macro INCREMENT
.mparam reg
    add reg, reg, 1
.endm

.macro DECREMENT
.mparam reg
    sub reg, reg, 1
.endm







.macro SLEEPNS
.mparam ns,inst,lab
 MOV r7, (ns/10)-1-inst
lab:
 SUB r7, r7, 1
 QBNE lab, r7, 0
.endm



.macro WAITNS
.mparam ns,lab
 MOV r8, 0x24000




 MOV r28, (ns)/5 - 20
lab:
 LBBO r9, r8, 0xC, 4

 QBGT lab, r9, r28
.endm


.macro WAIT_TIMEOUT
.mparam timeoutNs, timeoutLabel

    MOV r28, ((timeoutNs)/5 - 20)
    QBGT timeoutLabel, r28, r9
.endm


.macro RESET_COUNTER

  MOV r8, 0x24000
  LBBO r9, r8, 0, 4
  CLR r9, r9, 3
  SBBO r9, r8, 0, 4

  MOV r28, 0
  SBBO r28, r8, 0xC, 4

  SET r9, r9, 3
  SBBO r9, r8, 0, 4




.endm


.macro RAISE_ARM_INTERRUPT

  MOV R31.b0, 20 +16



.endm

START:




 LBCO r0, C4, 4, 4
 CLR r0, r0, 4
 SBCO r0, C4, 4, 4




 MOV r0, 0x00000120
 MOV r1, 0x22028
 ST32 r0, r1




 MOV r0, 0x00100000
 MOV r1, 0x2202C
 ST32 r0, r1


 MOV r2, #0x1
 SBCO r2, C24, 12, 4


 MOV r20, 0xFFFFFFFF





_LOOP:


 RAISE_ARM_INTERRUPT




 LBCO r0, C24, 0, 12


 QBEQ _LOOP, r2, #0


 RESET_COUNTER




 MOV r3, 0
 SBCO r3, C24, 8, 4


 QBEQ EXIT, r2, #0xFF







 MOV r8, 0x24000
 LBBO r2, r8, 0xC, 4
 SBCO r2, C24, 12, 4


 QBA _LOOP

EXIT:

 MOV r2, #0xFF
 SBCO r2, C24, 12, 4

 HALT

