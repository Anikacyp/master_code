cc=g++
ccflags=-O3
exe=main
objs=main.o Graph.o Model.o Heap.o BaseLine.o MonteCarlo.o Seed.o
$(exe):$(objs)
	$(cc) ${ccflags} -o $(exe) $(objs)
main.o: main.cpp Model.h Graph.h BaseLine.h
	$(cc) ${ccflags} -c main.cpp
Graph.o: Graph.cpp Graph.h Objects.h
	$(cc) ${ccflags} -c Graph.cpp
Model.o: Model.cpp Model.h Graph.h limit.h Objects.h
	$(cc) ${ccflags} -c Model.cpp
Heap.o: Heap.cpp Heap.h Objects.h
	$(cc) ${ccflags} -c Heap.cpp
BaseLine.o: BaseLine.cpp BaseLine.h MonteCarlo.h
	$(cc) ${ccflags} -c BaseLine.cpp
MonteCarlo.o: MonteCarlo.cpp MonteCarlo.h Objects.h Graph.h
	$(cc) ${ccflags} -c MonteCarlo.cpp
Seed.o: Seed.cpp Seed.h Graph.h BaseLine.h
	$(cc) ${ccflags} -c Seed.cpp
    
.PYTHON:clean
clean:
	-rm -fr *.o
