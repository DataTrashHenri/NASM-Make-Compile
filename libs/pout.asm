global pout64_from_buffer,pout64_from_arg

section .text
	pout64_from_buffer:	;printf(rdi=buffer_location)
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
	mov	rax,		1
	mov	rsi,		buffer64
push	rdi
	mov	rdi,		1
	mov	rdx,		8
	syscall
pop	rdi
	ret

section .data
	buffer64 times 8 db 0
