CC = g++

all: SoftCPU.cpp CPU_UTILS.cpp ASM.cpp ASM_UTILS.cpp LinesLib.cpp MyGeneralFunctions.cpp Stack.cpp 
	$(CC) ASM.cpp ASM_UTILS.cpp LinesLib.cpp MyGeneralFunctions.cpp -o ASM.exe
	$(CC) SoftCPU.cpp CPU_UTILS.cpp LinesLib.cpp MyGeneralFunctions.cpp Stack.cpp -o CPU.exe
	$(CC) DisASM.cpp DisASM_UTILS.cpp LinesLib.cpp MyGeneralFunctions.cpp -o DisASM.exe
	$(CC) CleanResults.cpp -o Clean.exe

clean :
	rm *.exe