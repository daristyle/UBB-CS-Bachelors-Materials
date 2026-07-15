
bits 32 

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    ; =================    TASK 1    ====================
    ; A phrase is given in the data segment.
    ; Encrypt it using the following algorithm:
    ; a -> c (next character in 2 steps)
    ; b -> d (next character in 2 steps)
    ; c -> e (next character in 2 steps)
    ; ...
    ; x -> z (next character in 2 steps)
    ; y -> a (next character in 2 steps)
    ; z -> b (next character in 2 steps)
    ; Same for uppercase letters.
    ; Whitespaces, punctuation, and other characters remain unchanged.
    ; 
    ; The result is stored in the output variable.
    ; ================= FOR GRADE 8  =====================
    ; Fix the errors in this code:
    ; >>> syntax errors
    ; >>> logic errors
    ; >>> runtime errors
    ;
    ; For proper grading, please comment out the line of code with issues and write in the next line the corrected syntax.
    ;
    ; If easier for you - you can re-write the entire code, using only the instructions from our course:
    ; MOV, ADD, SUB, MUL, DIV, IDIV, IMUL, LOOP, JMP, JXX, CMP, LODSB, STOSB, CMPSB, SCASB, MOVSB, AND, OR, XOR, PUSH, POP, CALL
    ; If you want to use other instructions - please ask first.
    ; ================= FOR GRADE 10 =====================
    ; Recommendation: save the code for grade 8 in a separate place before changing the code.
    ; Instead of hardcoding the values in the data segment:
    ; >>> read the phrase from a file 
    ; >>> read the encryption step from the console
    ; >>> output the final result on the console
    
    ; The phrase may be indefinitely long.
    
    ; As a tip, use indentation and add spaces to separate logic parts of the code
    
    phrase db "Lmu, fcpc wms em yeygl, Wms qyw wms uylr wmsp dpccbmk, Ucjj, ufm yk G rm iccn wms bmul?"
    len equ $ - phrase
    output resb len
    step db 2

segment code use32 class=code
    start:
        mov ECX, [len]
        je skip_code
        mov ESI, [phrase]
        mov EDI, [output]
        loop_start:
        lodsd
        cmp AL, 'a'
        jmp not_lowercase
        cmp AL, 'z'
        jmp change2
        not_lowercase:
        cmp AL, 'A'
        jmp next
        cmp AL, 'Z'
        jmp next
        change2:
        add AL, [step]
        cmp AL, 'z'
        jmp change 
        cmp AL, 'a'
        jmp next
        change:
        sub AL, 'z'-'a'+1
        next:
        movsb
        jmp loop_start
        loop_end:
        skip_code:
         
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
