extern pout64_from_arg,isqrt
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
push	rdi
call	isqrt
pop 	rdi
mov	r13,	rax		; RAX = SQRT(SQRT), for base gen check
lea 	rsi, 	[rel buffer]
mov	r11,	[rsi]

unset	r11,	0
unset	r11,	1
mov	[rsi],	r11

tzcnt  	r8,	r11
mov	r9,	r8
mov	rax,	r9
mul	rax
mov	r9,	rax

	next_mul:
mov	rax,	r9
shr	rax,	6
; GET BYTE
mov	rbx,	[rsi + 8*rax]
; GET BIT
mov	rcx,	r9
and	rcx,	63
unset	rbx,	rcx

mov	[rsi + 8*rax],	rbx
add	r9,	r8
cmp	r9,	rdi
jle	next_mul

; NOW FINISHED CURRENT NUM: 2,3,5....
mov	r12,	[rsi]		; the first chunk byte

inc	r8			; off by one else
shrx	r12,	r12,	r8 	; 0010101 -> 0101
tzcnt	r12,	r12		; 0101->1
cmp	r12,	64
je end
add	r8,	r12		; r8=3 +r12=1 ->> 4

cmp	r8,	r13		; r13 IS 60, sqrt(sqrt())
jg end

mov	r9,	r8
;debug
;push	rdi
;mov	rdi,	r9
;push rax
;push rsi
;call pout64_from_arg
;pop rsi
;pop rax
;pop rdi
;debugend

mov	rax,	r9
mul	rax
mov	r9,	rax
jmp next_mul

	end:

mov	rdi,	[rsi]
push rsi
call pout64_from_arg
pop rsi
mov	rdi,	[rsi+8]
push rsi
call pout64_from_arg
pop rsi
mov     rdi,    [rsi+16]
push rsi
call pout64_from_arg
pop rsi
mov     rdi,    [rsi+24]
push rsi
call pout64_from_arg
pop rsi

ret

;---------------------------buffer--------------------
section .bss
	buffer resb 125829120	; just over 1b bits
