all: fileWriter.o inputVal.o cubeVol.o circleArea.o binary.o diceRoller.o ccomp1.o -lm 
	gcc $^ -g -o $@

ccomp1.o: CComp1.c
	gcc -c -g -o $@ $< 

binary.o: binary.c
	gcc -c -g -o $@ $<

cubeVol.o: cubeVol.c
	gcc -c -g -o $@ $<

circleArea.o: circleArea.c
	gcc -c -g -o $@ $<

diceRoller.o: diceRoller.c
	gcc -c -g -o $@ $<

inputVal.o: inputVal.c
	gcc -c -g -o $@ $<
	
fileWriter.o: fileWriter.c
	gcc -c -g -o $@ $<

clean:
	rm -f *.o
	rm -f ccomp1
