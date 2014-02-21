.text
.global __syscall_cp_asm
.type   __syscall_cp_asm,@function
__syscall_cp_asm:

.global __cp_begin
__cp_begin:
	mov (%rdi),%eax
	test %eax,%eax
	jnz __cancel
	jmp __x32_syscall_cp_fixup
.global __cp_end
__cp_end:
	ret

.global __syscall_cp_internal
.type   __syscall_cp_internal,@function
__syscall_cp_internal:
	mov %rdi,%r11
	mov %rsi,%rax
	mov %rdx,%rdi
	mov %rcx,%rsi
	mov %r8,%rdx
	mov %r9,%r10
	mov 8(%rsp),%r8
	mov 16(%rsp),%r9
	mov %r11,8(%rsp)
	syscall
	ret
