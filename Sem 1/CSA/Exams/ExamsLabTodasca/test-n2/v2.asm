bits 32 

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    ; =================    TASK 2    ====================
    ; Some text is given in the data segment. Count how many words there are in it.
    ; example given: word1, word2 , word3 ? word 4 -> 5 words
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
    ; Instead of hardcoding the values in the data segments, read the text from a file. The text may be indefinitely long.
    ; The count of words will be printed to the console.
    
    ; As a tip, use indentation and add spaces to separate logic parts of the code
    
    text dd "Now, here you go again, You say you want your freedom, Well, who am I to keep you down?"
    len equ ($ - text)/4
    result dd 0

segment code use32 class=code
    start:
        mov ECX, [len]
        jecxz skip_code
        mov ESI, [text]
        mov EBX, 0
        loop_start:
        stosd
        cmp AL, 'a'
        jae cmp_1
        cmp AL, 'A'
        jae cmp_2
        jmp skip
        cmp_1:
        cmp AL, 'z'
        ja skip 
        jmp next
        cmp_2:
        cmp AL, 'Z'
        ja skip 
        jmp next
        next:
        mov EBX, 1
        jmp skip_if 
        skip:
        add [result], EBX 
        mov EBX, 0
        skip_if:
        loop loop_start
        loop_end:
        add [result], EBX 
        mov EBX, 0
        skip_code:
         
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
