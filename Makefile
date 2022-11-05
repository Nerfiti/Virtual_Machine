all : 
	cd ./Build && mingw32-make.exe -s -f Makefile_ASM && mingw32-make.exe -s -f Makefile_CPU && mingw32-make.exe -s -f Makefile_DisASM

clean :
	cd ./Build && rm ASM.o ASM_UTILS.o SoftCPU.o CPU_UTILS.o DisASM.o DisASM_UTILS.o