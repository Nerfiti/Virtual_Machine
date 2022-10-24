TARGET = ASM.exe
CC = g++ -c
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
CXXFLAGS = -IC:\Users\penko\Projects\Compiler\Generals

../Build/ASM.o ../Build/ASM_UTILS.o : ASM.cpp ASM_UTILS.cpp
	$(CC) $(CXXFLAGS) ASM.cpp -o ../Build/ASM.o
	$(CC) $(CXXFLAGS) ASM_UTILS.cpp -o ../Build/ASM_UTILS.o