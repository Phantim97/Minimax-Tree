.model flat, c
.code

Depth_ proc
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]	; eax = 'depth'
	mov ecx, 0			; ecx = depth size

Lp: shr eax, 1			; shift eax right by 1
	cmp eax, 0			; check if eax is 0
	jle DepthFound		; once eax hits 0 return 
	inc ecx				; depth++
	jmp Lp				; loop until depth found

DepthFound:
	mov eax, ecx		; store ecx into eax for return value
	pop ebp
	ret
Depth_ endp
end