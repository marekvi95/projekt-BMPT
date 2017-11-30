; Set offset for control register addresses (NEEDED)

#define __SFR_OFFSET 0

;***************************************************************************
;*
;* "div16u" - 16/16 Bit Unsigned Division
;*
;* This subroutine divides the two 16-bit numbers
;* "dd8uH:dd8uL" (dividend) and "dv16uH:dv16uL" (divisor).
;* The result is placed in "dres16uH:dres16uL" and the remainder in
;* "drem16uH:drem16uL".
;*
;* Number of words	:19
;* Number of cycles	:235/251 (Min/Max)
;* Low registers used	:2 (drem16uL,drem16uH)
;* High registers used  :5 (dres16uL/dd16uL,dres16uH/dd16uH,dv16uL,dv16uH,
;*			    dcnt16u)
;*
;***************************************************************************

    .global convtof
    .func convtof

convtof:
    movw	r18, r24    ;nacteni registroveho paru r24, r25(obsahuje teplotu v C) do reg r18, r19
    add	r18, r18        ;nasobeni deviti
    adc	r19, r19
    add	r18, r18
    adc	r19, r19
    add	r18, r18
    adc	r19, r19
    add	r24, r18
    adc	r25, r19        ;reg. par r24:r25 = T * 9
    movw	r18, r24    ;nacteni registroveho paru r24, r25(obsahuje teplotu v C) do reg r18, r19
    subi	r18, 0x60	; 96    od reg. r18 odečteme hodnotu 96
    sbci	r19, 0xFF	; 255   od reg. r19 odečteme hodnotu 255 a hodnotu carry
    ldi	r26, 0xCD	; 205   vlož konstantu do r26
    ldi	r27, 0xCC	; 204   vlož konstantu do r27
    mul	r26, r18    ;násobení r26 a r18
    movw	r22, r0 ;dale uz jenom pro otrle
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
    lsr	r25 ;deleni peti
    ror	r24
    lsr	r25
    ror	r24
    ret


    .endfunc





