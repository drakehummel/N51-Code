global main

section .data

	firstNum: times 100 db 0
	secondNum: times 100 db 0

section .bss					;this is for uninitialized variables in static memory

	firstNum_len resd 1			;length of firstNum  resd- reserve data
	secondNum_len resd 1
	firstNum_val resd 1			;int value of firstNum  resd- reserve data
	secondNum_val resd 1

section .text

	firstMsg: db "Enter your first number: ", 0
	secondMsg: db "Enter your second number: ", 0
	thirdMsg: db "You entered: ", 0
	gt: db '>'
	lt: db '<'
	eq: db '='

main:

				; PRINTING MESSAGE 1
	mov eax, 4					; write
	mov ebx, 1					; std out
	mov ecx, firstMsg			; messgae to be printed
	mov edx, 26 				; length of message
	int 80h						; execute system call. Looks at value in eax


				; READING USER INPUT
	mov eax, 3					; read
	mov ecx, firstNum			; ecx now holds the firstNum address
	mov edx, 100				; buffer length (max)
	int 80h						; execute

				; SAVING THE BYTES IN EAX
	mov [firstNum_len], eax

				; PRINTING MESSAGE 3
	mov eax, 4					; write
	mov ebx, 1					; std out
	mov ecx, thirdMsg
	mov edx, 14 				; read character
	int 80h

				; PRINTING FIRST NUMBER

	mov eax, 4					; write
	mov ebx, 1					; std out
	mov ecx, firstNum			; ecx now holds the firstNum address
	mov edx, [firstNum_len]
	int 80h

				; PRINTING MESSAGE 2

	mov eax, 4					; write
	mov ebx, 1					; std out
	mov ecx, secondMsg			; messgae to be printed
	mov edx, 27 				; length of message
	int 80h						; execute system call. Looks at value in eax


				; READING USER INPUT
	mov eax, 3					; read
	mov ecx, secondNum			; ecx now holds the secondNum address
	mov edx, 100				; buffer length (max)
	int 80h						; execute

	mov [secondNum_len], eax


				; PRINTING MESSAGE 3
	mov eax, 4					; write
	mov ebx, 1					; std out
	mov ecx, thirdMsg
	mov edx, 14 				; read character
	int 80h


					; PRINTING SECOND NUMBER

	mov eax, 4					; write
	mov ebx, 1					; std out
	mov ecx, secondNum			; ecx now holds the firstNum address
	mov edx, [secondNum_len]
	int 80h


					; CONVERTING FIRST NUMER TO AN INTEGER
	mov edx, firstNum
	xor eax, eax 				; zeros eax and causes eax to act as an accumulator
	call .test1
	mov [firstNum_val], eax 	; save converted value
	jmp .test2


.test1:

	movzx ecx, byte [edx] 		; retrives leftmost character. movzx - moves an unassigned value into a register and zero-extends it with zero

	inc edx
	cmp ecx, '0'				;; checks for a valid character
	jb .test1end				; if not, assume its a new line and end
	cmp ecx, '9'				;; checks for a valid character
	ja .test1end				; if not, assume its a new line and end
	sub ecx, '0'				;; convert character to a number
	imul eax, 10				; shift accumulator left
	add eax, ecx				; add current num to the accumulator
	jmp .test1					; loop to next character
	.test1end:
	ret




.test2:
					; CONVERTING SECOND NUMBER TO AN INTEGER
	mov edx, secondNum
	xor eax, eax 				; zeros eax and causes eax to act as an accumulator
	call .test1




;	movzx ecx, byte [edx] 		; retrives leftmost character. movzx - moves an unassigned value into a register and zero-extends it with zero

;	inc edx
;	cmp ecx, '0'				;; checks for a valid character
;	jb .test2end				; if not, assume its a new line and end
;	cmp ecx, '9'				;; checks for a valid character
;	ja .test2end				; if not, assume its a new line and end
;	sub ecx, '0'				;; convert character to a number
;	imul eax, 10				; shift accumulator left
;	add eax, ecx				; add current num to the accumulator
;	jmp .test2					; loop to next character
;	.test2end:


	mov [secondNum_val], eax 	; save converted value

					; PRINTING FIRST NUMBER
	mov eax, 4					; write
	mov ebx, 1					; std out
	mov ecx, firstNum			; ecx now holds the firstNum address
	mov edx, [firstNum_len]
	sub edx, 1					; removing the new line
	int 80h

					; EQUIVALENCY TEST

	mov eax, [firstNum_val]		; store first number in eax
	mov ebx, [secondNum_val]	; store second number in ebx
	cmp eax, ebx
	jb .lt
	ja .gt
	je .eq


.lt:
	mov ecx, lt
	jmp .print


.gt:
	mov ecx, gt
	jmp .print


.eq:
	mov ecx, eq


.print:
	mov eax, 4
	mov ebx, 1
	mov edx, 1
	int 80h

			; PRINTING NUMBER 2
	mov eax, 4
	mov ebx, 1
	mov ecx, secondNum
	mov edx, [secondNum_len]
	int 80h

	mov eax, 1				; return
	mov ebx, 0				; return code- good to go
	int 80h



