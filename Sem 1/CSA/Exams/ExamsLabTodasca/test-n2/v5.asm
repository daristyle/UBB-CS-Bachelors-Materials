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
    
    text db "Now, here you go again, You say you want your freedom, Well, who am I to keep you down?"
    len equ $ - text
    result dd 0

segment code use32 class=code
    start:
        mov ECX, len
        jecxz skip_code
        mov EDI, text 
        mov BL, 0
        loop_start:
        stosd
        cmp AL, 'a'
        jmp next
        cmp AL, 'A'
        jmp next2
        next:
        cmp AL, 'z'
        jmp next3 
        jmp is_character
        next2:
        cmp AL, 'Z'
        jmp next3 
        jmp is_character
        is_character:
        mov BL, 1
        jmp skip_if 
        next3:
        add result, BL 
        mov BL, 0
        skip_if:
        jmp loop_start
        loop_end:
        add result, BL 
        mov BL, 0
        skip_code:
         
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
