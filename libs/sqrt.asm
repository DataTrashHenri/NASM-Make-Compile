extern pout64_from_arg
global	isqrt

;-----------------------------------------------------------

section	.text

	isqrt:				; NOT SAVED: rax,rdi,r8,xmm0-4
mov		rax,	rdi
cvtsi2sd	xmm2,	rax		;S
shr		rax,	1
cvtsi2sd	xmm1,	rax		;xmm1 first estimate
mov		r8,	0		;iteration counter
movsd		xmm4,	[THRESHOLD]	; only used later for check after each iter

	loop:
movsd	xmm3,	xmm1			;store prev step

movsd 	xmm0,	xmm2 			;restore S in xmm0
divsd	xmm0,	xmm1			;xmm0 = S/x,xmm1 is x!!
addsd	xmm0,	xmm1			;xmm0 prefinished
movsd	xmm1,	[rel HALF]
mulsd	xmm1,	xmm0 			;xmm1 is prepeared for next iter

subsd		xmm3,	xmm1			;reached final (close)form?
cvtsd2si	rdi,	xmm1			;prep for writeout!!
comisd		xmm3,	xmm4			;threadhold reached
jb	loop_exit

;call	pout64_from_arg

inc	r8
cmp	r8,	1_000			;incase of really large num or float precision failure
jl	loop

	loop_exit:
;call	pout64_from_arg
mov rax,rdi
ret					; RDI HOLDS SQRT

;-------------------------------------------------------------

section	.rodata
HALF		dq	0.5
THRESHOLD	dq	0.00000000001
