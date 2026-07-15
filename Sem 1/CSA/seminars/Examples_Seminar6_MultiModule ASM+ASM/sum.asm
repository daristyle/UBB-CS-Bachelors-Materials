bits 32

global sum 

segment code use32 class=code
    sum:
        ; 3 paramas dd in rev order
        ; computes sum of param and returns result in EAX
        ; free stack in function
        mov eax, [esp+4] ; 1st param
        add eax, [esp+8]
        add eax, [esp+12]

        ret 3*4 ; free 3 pars on stack