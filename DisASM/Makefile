TARGET = DisASM.exe
CC = g++ -c
LINKER = g++
SRC = $(wildcard *.cpp)
OBJ = $(wildcard *.o) 
CXXFLAGS = -IC:\Users\penko\Projects\Compiler\Generals

$(TARGET) : obj
	$(LINKER) $(OBJ) -o $(TARGET) 

obj : $(SRC)
	$(CC) $(CXXFLAGS) $(SRC)

clean :
	del $(patsubst %.cpp, %.o, $(SRC))