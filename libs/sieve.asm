extern pout64_from_arg
global sieve_init, generate_base


section .text
;------------------------macros-----------------------
%macro set 2
bts	%1,	%2
%endmacro
%macro unset 2
btr	%1,	%2
%endmacro
;------------------------functions--------------------
	sieve_init:
mov	rdi,	buffer
mov	rcx,	125829120/8
mov	rax,	-1
rep	stosq
	ret

	generate_base:		;RDI= SQRT
lea 	rsi, 	[rel buffer]
mov	rax,	[rsi]

unset	rax,	0
unset	rax,	1
unset	rax, 	2
unset	rax,	15

mov 	r8,	3


mov	[rsi],	rax
mov	rdi,	rax
call pout64_from_arg
ret
;---------------------------buffer--------------------
section .bss
	buffer resb 125829120	; just over 1b bits
