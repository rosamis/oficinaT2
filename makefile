make:
	gcc -Wall -o objeto objeto.c lista.c
	gcc -Wall -o SimplifyObj SimplifyObj.c objeto.c lista.c -lm
	gcc -Wall -o ChopObj ChopObj.c objeto.c lista.c
	gcc -Wall -o Obj2Stl Obj2Stl.c objeto.c lista.c
