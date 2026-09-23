global pout64_from_buffer,pout64_from_arg

section .text
	pout64_from_buffer:	;printf(rdi=buffer_location) NOT SAVED: rax,rsi,rdx
	mov	rax,	1
	mov	rsi,	rdi
push	rdi
	mov	rdi,	1
	mov	rdx,	8
	syscall
pop	rdi
	ret

	pout64_from_arg:		;printf(rdi=value to print)
	mov	[buffer64],	rdi
push rcx
	push rax
	mov	rax,		1
	push rsi
	mov	rsi,		buffer64
	push rdi
	mov	rdi,		1
	push rdx
	mov	rdx,		8
	syscall
	pop rdx
	pop rdi
	pop rsi
	pop rax
pop rcx
	ret

section .data
	buffer64 times 8 db 0
