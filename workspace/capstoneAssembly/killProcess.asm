BITS 32

;global _start
;_start:
         ;push ebp
         ;mov ebp, esp



         mov ebx, edi       ; pid


         ;add esp, 4

         mov ecx, 15       ; sigterm
         mov eax, 0x25     ; syskill
         int 0x80	       ; call kernel.


		 ;mov esp, ebp
		 ;pop ebp
		 ret 4
