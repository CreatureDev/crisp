.cc.o:
	$(CC) $(CFLG) `llvm-config --cxxflags` -c $^
CC=g++
CFLG=-Wall -g 
LFLG=-L/usr/lib/llvm-3.5/lib -lLLVM-3.5 
OBJ=crisp.o crast.o
PRG=ctest

all:$(PRG)

cmain.o:cmain.c
	gcc $(CLFG) -c $^

ctest:cmain.o $(OBJ)
	$(CC) $(LLVM) $(LFLG) $(CFLG) -o $@ $^

clean:
	/bin/rm -f $(PRG) *.o a.out
