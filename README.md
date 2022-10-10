# Virtual Machine

This program allows you to perform the simplest arithmetic operations with integers.

---------------------------------------------------------------------------------------------

"ASM.exe"

To get the file "ASM.exe", it is necessary to compile the files "ASM.cpp", "ASM_UTILS.cpp", "LinesLib.cpp" and "MyGeneralFunctions.cpp"

"ASM.exe" translates "input.txt" into the machine code executed by the file "CPU.exe" and get the file "Listing.txt".

---------------------------------------------------------------------------------------------

"DisASM.exe"

To get the file "DisASM.exe", it is necessary to compile the files "DisASM.cpp", "DisASM_UTILS.cpp", "LinesLib.cpp" and "MyGeneralFunctions.cpp"

"DisASM.exe" translates "Code_machine.bin" to a text file with a description of the commands.

---------------------------------------------------------------------------------------------

"CPU.exe"

To get the file "CPU.exe", it is necessary to compile the files "SoftCPU.cpp", "CPU_UTILS.cpp", "LinesLib.cpp", "MyGeneralFunctions.cpp" and "Stack.cpp"

"CPU.exe" executes code from "Code_machine.bin" and writes the result to a file "Result.txt"

---------------------------------------------------------------------------------------------

"Clean.exe"

To get the file "Clean.exe", it is necessary to compile the file "CleanResults.cpp"

"Clean.exe" deletes files "DisASM Result.txt" , "Listing.txt" and "Result.txt"

---------------------------------------------------------------------------------------------

"input.txt"

The file must consist of valid commands, located on separate lines. If the command has arguments, then they must be on the same line as the command and be separated from it by a space

---------------------------------------------------------------------------------------------

Valid commands (with their numbers in the machine code):

1 = PUSH [one argument] -- push number-argument on the CPU stack

2 = ADD                 -- adds       the top 2 numbers from the stack

3 = SUB                 -- subtracts  the top number of the stack from the penultimate one

4 = MUL                 -- multiplies the top 2 numbers from the stack

5 = DIV                 -- divides    the penultimate number in the stack by the top number of the stack

6 = OUT                 -- prints the top number of the stack to a file "Result.txt"

7 = HLT                 -- terminates the CPU

---------------------------------------------------------------------------------------------
