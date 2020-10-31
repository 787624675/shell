default: myipc init.c mother.c father.c son.c daughter.c
	gcc -o init myipc.o init.c
	gcc -o mother myipc.o mother.c
	gcc -o father myipc.o father.c
	gcc -o son myipc.o son.c
	gcc -o daughter myipc.o daughter.c
myipc: myipc.c
	gcc -c myipc.c