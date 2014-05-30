COMPILER=g++
EXE=main
OBJ=main.o Graph.o PP.o
$(EXE):$(OBJ)
	$(COMPILER) -o $(EXE) $(OBJ)
main.o: main.cpp Graph.h PP.h
	$(COMPILER) -c main.cpp
Graph.o: Graph.cpp Graph.h
	$(COMPILER) -c Graph.cpp
PP.o: PP.cpp PP.h
	$(COMPILER) -c PP.cpp

.PYTHON:clean
clean:
	-rm -fr *.o