bits 32 

global start        

extern exit
import exit msvcrt.dll

segment data use32 class=data
    ; =================    TASK 3    ====================
    ; You are given an array of numbers. Create a new array of numbers, with the following rules:
    ; if a[i] is zero, then b[i] = length of the array 
    ; if a[i] > 0, then b[i] = a[i] / 2
    ; if a[i] < 0, then b[i] = a[i] * 2
    ; The array is made up of doublewords!
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
    ; Instead of hardcoding the values in the data segments, read the array from the console AND write the final array in a file.
    ; You can use any name for the file. Suggestion: array.out
    ; You are not given the length of the array initially - you will read numbers until you read the number 42.
    
    ; Other tips:
    ; >>> use indentation and add spaces to separate logic parts of the code
    
    array dd 10, 0, 0, -3, -10, 173
    len equ $-array
    result dd len
    
segment code use32 class=code
    start:
        mov ESI, 0
        while_loop_start:
        cmp ESI, [len] 
        ja while_loop_end
        mov EAX, [array + 4*ESI]
        inc ESI
        cmp AL, 0
        jmp skip
        jmp skip2
        jmp skip3
        skip3:
        mov EBX, EAX 
        shl EBX, 1
        jmp if_done
        skip2:
        mov EBX, EAX
        shr EBX, 1
        jmp if_done
        skip:
        mov EBX, len
        if_done:
        mov [result + 4*ESI], EBX
        jmp while_loop_start
        while_loop_end:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
