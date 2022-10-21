all : 
	cd .\ASM && mingw32-make.exe -s
	cd .\CPU &&	mingw32-make.exe -s
	cd .\DisASM && mingw32-make.exe -s

clean :
	cd .\ASM && mingw32-make.exe clean -s
	cd .\CPU &&	mingw32-make.exe clean -s
	cd .\DisASM && mingw32-make.exe clean -s