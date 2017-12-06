; Set offset for control register addresses (NEEDED)

#define __SFR_OFFSET 0

;***************************************************************************
;*
;* "convtof" - Conversion between Celsisus and Fahrnheit scales
;*
;* Function is called from C, and has one input and one output paremetres
;*
;* Conversion of temperature scales using equation:
;*   C*9+160
;* ------------  = F
;*      5
;*
;*
;***************************************************************************

    .global convtof
    .func convtof

convtof:
    push r0             ; save r0 to stack
    movw	r18, r24    ; input value load
    add	r18, r18        ;multiplication by 9
    adc	r19, r19
    add	r18, r18
    adc	r19, r19
    add	r18, r18
    adc	r19, r19
    add	r24, r18
    adc	r25, r19        ;r24:r25 = C * 9
    movw	r18, r24    ;nacteni registroveho paru r24, r25
    subi	r18, 0x60	; 96    subtract value 96 from r18
    sbci	r19, 0xFF	; 255   subtract 255+carry
    ldi	r26, 0xCD	    ; 205   load 205 to r26
    ldi	r27, 0xCC	    ; 204   load 204 to r27
    mul	r26, r18        ; multiplication of r26 r18
    movw	r22, r0     
    mul	r27, r19
    movw	r24, r0
    mul	r26, r19
    add	r23, r0
    adc	r24, r1
    eor	r1, r1
    adc	r25, r1
   	mul	r27, r18
    add	r23, r0
    adc	r24, r1
    eor	r1, r1
    adc	r25, r1
    lsr	r25           ; division by 5
    ror	r24
    lsr	r25
    ror	r24
    clr r1            ; clear R1
    pop r0            ; restore r0
    ret               ; return result


    .endfunc
