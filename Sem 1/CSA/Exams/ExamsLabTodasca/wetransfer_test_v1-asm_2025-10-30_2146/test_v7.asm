bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - byte
    ; b - word
    ; c a word made up in the following way:
    ;     bits 0-3 of c are 1
    ;     bits 4-11 are the same as a
    ;     bits 12-15 are the same as bits 12-15 of b
    
    ; compute the following:
    ; b*c/a + b/c - signed representation

    a db 10
    b dw 10
    c dw 0
    
    ; from grade 9 to grade 10:
    ;    optimize the solution so it uses even less lines of code (remove unneeded lines of code)
    ;    remove the usage of the additional variable c
    
; our code starts here
segment code use32 class=code
    start:
        mov AX, word [b]
        mov AL, [a]
        mov CL, 0x4
        shl AX, Cl
        or AX, 0_1111b
        mov AX, [c]
        mov AX, [b]
        mul AX, word [c]
        mov CX, AX
        mov AL, [a]
        cwde
        mov BX, AX
        mov AX, CX
        idiv BX
        mov BX, AX
        mov AX, [b]
        idiv [c]
        add BX, AX
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
