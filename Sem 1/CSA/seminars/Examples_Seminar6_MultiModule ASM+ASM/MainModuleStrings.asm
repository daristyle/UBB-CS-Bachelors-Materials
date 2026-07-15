bits 32 
global start        

extern exit , printf
extern concatenate
import exit msvcrt.dll 
import printf msvcrt.dll 
segment data use32 class=data
    s1 db 1, 2, 3, 4, 5, 6
    len1 equ $-s1
    s2 db 20, 30, 45, 72, 85
    len2 equ $-s2
    ; compute s3 by concatenating odd elements (unsigned) from s1 and s2 (strings of bytes)
    s3 times len1+len2 db 0 
    len3 db 0
    format_print db "%d ", 0
    
segment code use32 class=code
    
    start:
        ; concatenate(s1, len1, s2, len2, & s3 )  
        ; s3 is output computed by concatenating odd elements from s1 and s2
        ; returns in EAX the length of s3 
        ; modify registers EAX, ECX, ESI, EDI ...
        ; free the stack in main          
        push dword s3 
        push dword len2
        push dword s2 
        push dword len1 
        push dword s1 
        call concatenate
        add esp, 4*5 
        
        mov [len3], AL 
    
        ; print s3 
        mov ECX, EAX 
        mov ESI, s3
        print_loop:
            mov EAX, 0 ; unsigned conversion to doubleword
            LODSB ; AL=[esi], esi+1
            ; printf("%d ", EAX);
            
            push ECX 
            push dword EAX
            push dword format_print
            call [printf]
            add esp, 4*2 
            pop ECX 
           
        loop print_loop
        
    
       ; exit(0)
        push    dword 0      
        call    [exit]   