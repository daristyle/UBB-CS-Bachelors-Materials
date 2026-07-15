bits 32

global concatenate

segment code use32 class=code
   concatenate:
        ; concatenate(s1, len1, s2, len2, & s3 )  
        ; s3 is output computed by concatenating odd elements from s1 and s2
        ; returns in EAX the length of s3 
        ; modify registers EAX, ECX, ESI, EDI ...
        ; free the stack in main  
        mov ESI, [ESP+4] ; s1
        mov EDI, [ESP+20]; s3 
        mov ECX, [ESP+8]; len1 
        mov EBX, 0
        jecxz .end1
        .copy_odd1:
            LODSB; AL=[esi], esi+1
            mov DL,2
            mov AH, 0 ; AX=elem 
            div DL    ; AL=AX/DL; AH=AX%DL
            cmp AH, 0
            je .skip1
               mov AL, [ESI-1]
               STOSB ; [EDI]=AL, edi+1
               inc EBX
            .skip1:
        loop .copy_odd1
        .end1: 
        
        
        mov ESI, [ESP+12] ; s2
        mov ECX, [ESP+16]; len2 
        jecxz .end2
        .copy_odd2:
            LODSB; AL=[esi], esi+1
            mov DL,2
            mov AH, 0 ; AX=elem 
            div DL    ; AL=AX/DL; AH=AX%DL
            cmp AH, 0
            je .skip2
               mov AL, [ESI-1]
               STOSB ; [EDI]=AL, edi+1
               inc EBX
            .skip2:
        loop .copy_odd2
        .end2:
        
        mov EAX, EBX
        ret 
