bits 32

global _sum

segment data public data use32

segment code public code use32

; definire procedura
_sum:
    ; Codul de intrare
	push ebp
	mov ebp, esp
    
	mov eax, [ebp+8]
	add eax, [ebp+12]

    ; Codul de iesire
	mov esp, ebp
	pop ebp
    ret
