extern cmain
extern add
extern exit
extern printf

section .data

section .text
global main

main:
	PUSH 1
	PUSH 2
	;CALL cmain
	CALL add	

	PUSH eax 
	CALL exit
