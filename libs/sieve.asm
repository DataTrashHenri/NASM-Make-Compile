extern pout64_from_arg,isqrt, sieve_chunk
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
mov	rcx,	12960000/8
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
;call pout64_from_arg
pop rsi
mov	rdi,	[rsi+8]
push rsi
;call pout64_from_arg
pop rsi
mov     rdi,    [rsi+16]
push rsi
;call pout64_from_arg
pop rsi
mov     rdi,    [rsi+24]
push rsi
;call pout64_from_arg
pop rsi

ret
;---------------------------END-BASE-----------------

sieve_chunk:			;rdi = cstart, rsi= cend
lea	r10,	[rel buffer]


;mov	rcx,	2
;call	sieve_prime_in_chunk


xor	r14,	r14
xor	rbx,	rbx
.sieve_loop:

mov 	rax,	[r10 + 8 * r14]
shrx	rax,	rax,	rbx

tzcnt	rbx,	rax

cmp	rbx,	64
jl	.iter_loop
inc	r14
call	pout64_from_arg
;aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

;check for last byte
mov	rax,	r14
shl	rax,	6
add	rax,	64
cmp	rax,	rsi
jge	.end
jmp 	.sieve_loop

.iter_loop:	;rbx is %64, r14 qbyte

mov	r15,	r14
shl	r15,	6
add	r15,	rbx	; NEXT PRIME

push rdi
mov	rdi,	r15
call	pout64_from_arg
pop rdi

mov	rcx,	r15

push rbx		; NEEDED=>>>>>>> r14,(r10)
call	sieve_prime_in_chunk
pop rbx

;inc	r14

; last byte check
mov     rax,    r14
shl     rax,    6
add     rax,    64
cmp     rax,    rsi
jge     .end

jmp	.sieve_loop

.end:
	ret

sieve_prime_in_chunk:   ;rdi = cstart, rsi= cend, rcx= prime

mov     rax,    rdi
xor     rdx,    rdx
div     rcx
inc     rax             ; rax is 3600/p +1..
cmp     rax,    rcx	; p vs. n
cmovl	rax,	rcx	; n<p? n=p, bigger of both
mul	rcx

cmp	rax,	rsi
jg	return

start_marking:          ;intern, rax=   first multiple
mov	r8,	rax
shr	r8,	6	; R8 is 64-CHUNK

mov	r9,	rax
and	r9,	63	; R9 IS BIT


mov	rbx,	[r10+ 8*r8]
.loop:
unset	rbx,	r9
add	r9,	rcx	; += prime
cmp	r9,	64
jle	.loop

mov 	[r10 + 8*r8],	rbx
mov	r11,	r8
shl	r11,	6
add	r9,	r11		; 3602 +64...

push	rdi
;mov	rdi,	[r10 + 8*r8]
;call	pout64_from_arg
pop	rdi

cmp	r9,	rsi
jge 	.end
mov	rax,	r9
;sub	rax,	rcx		; HÄHHH
jmp	start_marking

.end:
        ret
return:
	ret
;---------------------------buffer--------------------
section .bss
;	buffer resb 125829120	; just over 1b bits
	buffer resb 12960000
