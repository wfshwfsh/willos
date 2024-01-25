; -----------------------------------
; define mboot magic
; define mboot page_align
; define mboot mem info
; -----------------------------------
MBOOT_HEADER_MAGIC	equ	0x1BADB002

MBOOT_PAGE_ALIGN	equ 1<<0
MBOOT_MEM_INFO		equ 1<<1

MBOOT_HEADER_FLAGS	equ	(MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO)
MBOOT_CHECKSUM		equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

; Compile with 32-bit
[BITS 32]

section .text
boot:
dd MBOOT_HEADER_MAGIC
dd MBOOT_HEADER_FLAGS
dd MBOOT_CHECKSUM

[GLOBAL start]
[GLOBAL glb_mboot_ptr]
[EXTERN kern_entry]
start:
	cli		;disable int
	
	; setting stack ptr
	mov esp, STACK_TOP
	mov ebp, 0
	and esp, 0FFFFFFF0H
	mov [glb_mboot_ptr], ebx
	call kern_entry
	
stop:
	hlt
	jmp	stop

; data
;section .data
;dd STACK_TOP

; bss
section .bss
stack:
	resb 0x8000

glb_mboot_ptr:
	resb 4

STACK_TOP equ $-stack-1













