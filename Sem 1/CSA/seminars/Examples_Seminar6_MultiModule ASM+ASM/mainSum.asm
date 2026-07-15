bits 32 
global start        

extern exit, scanf, printf  
extern sum              
import exit msvcrt.dll  
import scanf msvcrt.dll  
import printf msvcrt.dll    
segment data use32 class=data
    a dd 0
    b dd 0
    c dd 0
    format_print db "Give a number ", 0
    format db "%d", 0
    format_sum db "%d + %d + %d = %d", 0
    
segment code use32 class=code

    start:
        ; printf("Give a number")
        push dword format_print
        call [printf]
        add esp, 4 
        ; scanf("%d", &a)
        push dword a 
        push dword format 
        call [scanf]
        add esp, 2*4
        
          ; printf("Give a number")
        push dword format_print
        call [printf]
        add esp, 4 
        ; scanf("%d", &b)
        push dword b 
        push dword format 
        call [scanf]
        add esp, 2*4
        
           ; printf("Give a number")
        push dword format_print
        call [printf]
        add esp, 4 
        ; scanf("%d", &c)
        push dword c 
        push dword format 
        call [scanf]
        add esp, 2*4
        
        ; sum(a, b, c)
        push dword [c]
        push dword [b]
        push dword [a]
        call sum 
        
        ;printf("%d + %d + %d = %d", a, b, c, EAX)
        push dword EAX 
        push dword [c]
        push dword [b]
        push dword [a]
        push dword format_sum
        call [printf]
        add esp, 5*4
    
        ; exit(0)
        push    dword 0      
        call    [exit]      
