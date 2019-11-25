











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




 MOV r20, 0x00000000
 MOV r21, 0x00000000
 MOV r22, 0x02C3FFFE
 MOV r23, 0x0003C000



 MOV r24, 0x44E07000 | 0x190
 MOV r25, 0x4804c000 | 0x190
 MOV r26, 0x481AC000 | 0x190
 MOV r27, 0x481AE000 | 0x190

 SBBO r20, r24, 0, 4
 SBBO r21, r25, 0, 4
 SBBO r22, r26, 0, 4
 SBBO r23, r27, 0, 4


 WAITNS 220000, wait_preamble_low


 MOV r24, 0x44E07000 | 0x194
 MOV r25, 0x4804c000 | 0x194
 MOV r26, 0x481AC000 | 0x194
 MOV r27, 0x481AE000 | 0x194

 SBBO r20, r24, 0, 4
 SBBO r21, r25, 0, 4
 SBBO r22, r26, 0, 4
 SBBO r23, r27, 0, 4


 WAITNS (220000+113000), wait_preamble_high1





 MOV r24, 0x44E07000 | 0x190
 MOV r25, 0x4804c000 | 0x190
 MOV r26, 0x481AC000 | 0x190
 MOV r27, 0x481AE000 | 0x190

 SBBO r20, r24, 0, 4
 SBBO r21, r25, 0, 4
 SBBO r22, r26, 0, 4
 SBBO r23, r27, 0, 4



 WAITNS (220000+113000+32000), wait_zeroframe_low


 RESET_COUNTER

l_word_loop:

 MOV r6, 0

 l_bit_loop:

  MOV r2, 0
 MOV r3, 0
 MOV r4, 0
 MOV r5, 0




  LBBO r10, r0, 1*24*4+0*4, 16*4

  QBBS channel_0_zero_skip, r10, r6
 SET r4, r4, 1
 channel_0_zero_skip: 

  QBBS channel_1_zero_skip, r11, r6
 SET r4, r4, 2
 channel_1_zero_skip: 

  QBBS channel_2_zero_skip, r12, r6
 SET r4, r4, 3
 channel_2_zero_skip: 

  QBBS channel_3_zero_skip, r13, r6
 SET r4, r4, 4
 channel_3_zero_skip: 

  QBBS channel_4_zero_skip, r14, r6
 SET r4, r4, 5
 channel_4_zero_skip: 

  QBBS channel_5_zero_skip, r15, r6
 SET r4, r4, 6
 channel_5_zero_skip: 

  QBBS channel_6_zero_skip, r16, r6
 SET r4, r4, 7
 channel_6_zero_skip: 

  QBBS channel_7_zero_skip, r17, r6
 SET r4, r4, 8
 channel_7_zero_skip: 

  QBBS channel_8_zero_skip, r18, r6
 SET r4, r4, 9
 channel_8_zero_skip: 

  QBBS channel_9_zero_skip, r19, r6
 SET r4, r4, 10
 channel_9_zero_skip: 

  QBBS channel_10_zero_skip, r20, r6
 SET r4, r4, 11
 channel_10_zero_skip: 

  QBBS channel_11_zero_skip, r21, r6
 SET r4, r4, 12
 channel_11_zero_skip: 

  QBBS channel_12_zero_skip, r22, r6
 SET r4, r4, 13
 channel_12_zero_skip: 

  QBBS channel_13_zero_skip, r23, r6
 SET r4, r4, 14
 channel_13_zero_skip: 

  QBBS channel_14_zero_skip, r24, r6
 SET r4, r4, 15
 channel_14_zero_skip: 

  QBBS channel_15_zero_skip, r25, r6
 SET r4, r4, 16
 channel_15_zero_skip: 


  LBBO r10, r0, 1*24*4+16*4, 8*4

  QBBS channel_16_zero_skip, r10, r6
 SET r4, r4, 17
 channel_16_zero_skip: 

  QBBS channel_17_zero_skip, r11, r6
 SET r4, r4, 22
 channel_17_zero_skip: 

  QBBS channel_18_zero_skip, r12, r6
 SET r4, r4, 23
 channel_18_zero_skip: 

  QBBS channel_19_zero_skip, r13, r6
 SET r4, r4, 25
 channel_19_zero_skip: 

  QBBS channel_20_zero_skip, r14, r6
 SET r5, r5, 14
 channel_20_zero_skip: 

  QBBS channel_21_zero_skip, r15, r6
 SET r5, r5, 15
 channel_21_zero_skip: 

  QBBS channel_22_zero_skip, r16, r6
 SET r5, r5, 16
 channel_22_zero_skip: 

  QBBS channel_23_zero_skip, r17, r6
 SET r5, r5, 17
 channel_23_zero_skip: 






  MOV r20, 0x00000000
 MOV r21, 0x00000000
 MOV r22, 0x02C3FFFE
 MOV r23, 0x0003C000






  AND r9, r6, 7
  QBNE skip_stop_bits, r9, 0

   WAITNS 4000, wait_lastframe_in_stop_end


   MOV r24, 0x44E07000 | 0x194
 MOV r25, 0x4804c000 | 0x194
 MOV r26, 0x481AC000 | 0x194
 MOV r27, 0x481AE000 | 0x194

   SBBO r20, r24, 0, 4
 SBBO r21, r25, 0, 4
 SBBO r22, r26, 0, 4
 SBBO r23, r27, 0, 4




   WAITNS 12000, wait_stop_bit


   RESET_COUNTER


   MOV r24, 0x44E07000 | 0x190
 MOV r25, 0x4804c000 | 0x190
 MOV r26, 0x481AC000 | 0x190
 MOV r27, 0x481AE000 | 0x190

   SBBO r20, r24, 0, 4
 SBBO r21, r25, 0, 4
 SBBO r22, r26, 0, 4
 SBBO r23, r27, 0, 4





  skip_stop_bits:







  INCREMENT r6

  MOV r24, 0x44E07000 | 0x190
 MOV r25, 0x4804c000 | 0x190
 MOV r26, 0x481AC000 | 0x190
 MOV r27, 0x481AE000 | 0x190




  MOV r10, 0x44E07000 | 0x194

  MOV r11, 0x4804c000 | 0x194

  MOV r12, 0x481AC000 | 0x194

  MOV r13, 0x481AE000 | 0x194



  XOR r14, r2, r20
  XOR r15, r3, r21
  XOR r16, r4, r22
  XOR r17, r5, r23


  WAITNS 4000, wait_lastframe_end


  RESET_COUNTER


  SBBO r2, r24, 0, 4

  SBBO r14, r10, 0, 4


  SBBO r3, r25, 0, 4

  SBBO r15, r11, 0, 4


  SBBO r4, r26, 0, 4

  SBBO r16, r12, 0, 4


  SBBO r5, r27, 0, 4

  SBBO r17, r13, 0, 4




  QBNE l_bit_loop, r6, 24



 ADD r0, r0, 48 * 4
 DECREMENT r1
 QBNE l_word_loop, r1, #0


 MOV r20, 0x00000000
 MOV r21, 0x00000000
 MOV r22, 0x02C3FFFE
 MOV r23, 0x0003C000

 MOV r24, 0x44E07000 | 0x194
 MOV r25, 0x4804c000 | 0x194
 MOV r26, 0x481AC000 | 0x194
 MOV r27, 0x481AE000 | 0x194

 SBBO r20, r24, 0, 4
 SBBO r21, r25, 0, 4
 SBBO r22, r26, 0, 4
 SBBO r23, r27, 0, 4



 SLEEPNS 2504800, 4, wait_end_high





 MOV r8, 0x24000
 LBBO r2, r8, 0xC, 4
 SBCO r2, C24, 12, 4


 QBA _LOOP

EXIT:

 MOV r2, #0xFF
 SBCO r2, C24, 12, 4



 MOV R31.b0, 20 +16




 HALT

