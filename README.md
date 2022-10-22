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

1  = PUSH [one argument] -- push number-argument on the CPU stack

2  = ADD                 -- adds the top 2 numbers from the stack

3  = SUB                 -- subtracts the top number of the stack from the penultimate one

4  = MUL                 -- multiplies the top 2 numbers from the stack

5  = DIV                 -- divides the penultimate number in the stack by the top number of the stack

6  = DUP                 -- duplicate last stack element

7  = OUT                 -- prints the top number of the stack to a file "Result.txt"

8  = JMP  [one argument] -- jump to mark-argument (mark-argument must be ended by ':')

9  = JB   [one argument] -- jump to mark-argument if penultimate stack element <  last one

10 = JBE  [one argument] -- jump to mark-argument if penultimate stack element <= last one

11 = JA   [one argument] -- jump to mark-argument if penultimate stack element >  last one

12 = JAE  [one argument] -- jump to mark-argument if penultimate stack element >= last one

13 = JE   [one argument] -- jump to mark-argument if penultimate stack element == last one

14 = JNE  [one argument] -- jump to mark-argument if penultimate stack element != last one

15 = POP  [one argument] -- put the top number of the stack to the RAM or Register

16 = DUMP                -- displays detailed information about the current state of the processor

17 = CALL [one argument] -- call the functions named [argument]. Argument must be ended by ':'

18 = RET                 -- return the processor to the place of the function call

15 = HLT                 -- terminates the CPU

---------------------------------------------------------------------------------------------

REGISTERS

You can use 4 registert: RAX, RBX, RCX, RDX.

For example, to put the number 5 in the register RCX you need to use the commands:
"push 5"
"pop RCX"

---------------------------------------------------------------------------------------------

RAM

To put a number in the tenth memory cell, use the command (the stack must not be empty):

"pop [10]"

OR

"push 10"
"pop RBX"
"pop [RBX]"

OR

"push 5"
"pop RDX"
"pop [5+RDX]" or "pop [RDX+5]"

-----------------------------------------------------------------------------------------------
