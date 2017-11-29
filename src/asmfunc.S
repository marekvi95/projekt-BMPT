; Set offset for control register addresses (NEEDED)
#define __SFR_OFFSET 0

;Defines I/O port aliases
#include <avr/io.h>


.global asm_convert
.func asm_convert


asm_convert:
    push r18            ;Backup all registers going to use
    push r19            ;Backup
    push r31            ;Backup
    mov r31,r24
    ldi  r18, 51
    mul r31,r18
    inc r1
    lsr r1
    mov r31,r1
    mov r24,r31
    pop r31
    pop r19
    pop r18
    ret







.endfunc



