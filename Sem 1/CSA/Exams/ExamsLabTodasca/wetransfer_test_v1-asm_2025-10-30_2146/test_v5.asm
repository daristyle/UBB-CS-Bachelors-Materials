bits 32 
global start        
extern exit
import exit msvcrt.dll
                          
segment data use32 class=data
    ; signed representation
    ; a,b,c - byte 
    ; (a + a*b + a*b*c) / 100
    a db -1
    b db -2
    c db 10
    
    ; from grade 9 to grade 10:
    ;    optimize the solution so it uses even less lines of code (remove unneeded lines of code)
    ;    >>> explain your process of thinking
    
segment code use32 class=code
    start:
        xor EAX, EAX
        mov AL, [a]
        mov BX, AX
        mov AL, [a]
        mov CL, [b]
        mul CL
        add BX, AX 
        mov AL, [a]
        mov CL, [b] 
        mul CL
        mov CX, AX
        mov word [c]
        adc AX, BX 
        adc DX, 0 
        idiv 100b
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
