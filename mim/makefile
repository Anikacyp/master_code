COMPILER=g++
EXE=main
OBJ=Graph.o main.o Network.o PP.o
$(EXE):$(OBJ)
	$(COMPILER) -o $(EXE) $(OBJ)
main.o: main.cpp Graph.h Network.h PP.h
	$(COMPILER) -c main.cpp
Graph.o: Graph.cpp Graph.h
	$(COMPILER) -c Graph.cpp
Network.o: Network.cpp Network.h
	$(COMPILER) -c Network.cpp
PP.o: PP.cpp PP.h
	$(COMPILER) -c PP.cpp

.PYTHON:clean
clean:
	-rm -fr *.o