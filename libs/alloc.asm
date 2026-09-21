global alloc_n,free_n
section	.text



	alloc_n:
mov rsi,rdi

mov     rax, 9          ; syscall: mmap
mov     rdi, 0          ; addr = NULL → kernel chooses
mov     rdx, 3          ; PROT_READ | PROT_WRITE
mov     r10, 0x22       ; MAP_PRIVATE | MAP_ANONYMOUS
mov     r8,  -1         ; fd = -1 for anonymous
mov     r9,  0          ; offset = 0
syscall			; POINTER IN RAX!!!!
ret

	free_n:
; rdi = pointer
; rsi = size

mov     rax, 11         ; syscall: munmap
syscall
ret
