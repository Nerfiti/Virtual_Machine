all : 
	cd ./Build && mingw32-make.exe -s -f Makefile_ASM && mingw32-make.exe -s -f Makefile_CPU && mingw32-make.exe -s -f Makefile_DisASM
