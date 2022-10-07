CC = g++

all: SoftCPU.cpp FirstASM.cpp LinesLib.cpp MyGeneralFunctions.cpp Stack.cpp 
	$(CC) FirstASM.cpp LinesLib.cpp MyGeneralFunctions.cpp -o ASM.exe
	$(CC) SoftCPU.cpp LinesLib.cpp MyGeneralFunctions.cpp Stack.cpp -o CPU.exe
	$(CC) DisASM.cpp LinesLib.cpp MyGeneralFunctions.cpp -o DisASM.exe
	$(CC) CleanResults.cpp -o Clean.exe

clean :
	rm *.exe