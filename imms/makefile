cc=g++
ccflags=-O3 -std=c++11
exe=main
objs=main.o Graph.o Model.o
$(exe):$(objs)
	$(cc) ${ccflags} -o $(exe) $(objs)
main.o: main.cpp Model.h
	$(cc) ${ccflags} -c main.cpp
Graph.o: Graph.cpp Graph.h Objects.h
	$(cc) ${ccflags} -c Graph.cpp
Model.o: Model.cpp Model.h Graph.h limit.h Objects.h
	$(cc) ${ccflags} -c Model.cpp
.PYTHON:clean
clean:
	-rm -fr *.o