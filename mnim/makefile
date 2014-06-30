cc=g++
ccflags=-O3 -std=c++11
exe=main
obj=main.o Graph.o Model.o Seed.o Heap.o

$(exe):$(obj)
	$(cc) ${ccflags} -o $(exe) $(obj)
main.o: main.cpp Model.h
	$(cc) ${ccflags} -c main.cpp
Graph.o: Graph.cpp Graph.h BaseObj.h
	$(cc) ${ccflags} -c Graph.cpp
Model.o: Model.cpp Model.h Graph.h limit.h
	$(cc) ${ccflags} -c Model.cpp
Seed.o: Seed.cpp Seed.h Model.h BaseObj.h Heap.h
	$(cc) ${ccflags} -c Seed.cpp
Heap.o: Heap.cpp Heap.h
	$(cc) ${ccflags} -c Heap.cpp
.PYTHON:clean
clean:
	-rm -fr *.o