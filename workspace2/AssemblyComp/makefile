all: assemblycomp.asm
	nasm -f elf32 -g assemblycomp.asm
	gcc -m32 -lc -o assemblycompexe assemblycomp.o
	
clean:
	rm *.o assemblycompexe
	