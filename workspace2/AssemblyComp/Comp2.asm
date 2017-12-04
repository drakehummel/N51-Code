section .text

global main

main:
        call toUpper
        call print
        mov eax,1         ; exiting
        mov ebx,0         ; with a status of 0
        int 80h           ; sys call to exit

toUpper:
        push ecx
        mov ecx, string

checking:
        mov al,[ecx]      ; ecx is the pointer, so [ecx] the current char
        cmp al,0x00       ; compaing the lowest byte of eax (al) to 0x0
        je done           ; jump if equal, if not move on

        cmp al,0x61       ; if it is less than hex 'a'
        jb next_please    ; jump if below to next please
        cmp al,0x7a       ; if it is more than hex 'z'
        ja next_please    ; jump if above to next please.....this line and the three above are only for non lowercase chars

        sub al,0x20       ; subtract hex 20 from the lowercase letter to make it uppercase ex. a = 61 A = 41
        mov [ecx],al      ; moving what I modified in al back to ecx

next_please:
        inc ecx           ; incrementing the pointer in ecx by 1 to move to the next char
        jmp checking

done:
        pop ecx
        ret

print:
        push ecx           ; using push to preserve register context (local scope)
        push edx

        mov ecx, string    ; what to print
        mov edx, len       ; length of string to be printed
        mov ebx, 1         ; std out
        mov eax, 4         ; print
        int 80h            ; sys call to print

        pop edx			   ; using pop to restore register context (destroying the local scope of that register)
        pop ecx
        ret


section .data

string: db "The quick brown fox Jumps over THE lazy dog", 0x0a, 0x00      ; define byes (db)
len equ $ - string                                        ; special syntax to subtract the current pointer from the string to get the size of it
