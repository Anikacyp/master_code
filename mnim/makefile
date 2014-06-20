cc=g++
exe=main
obj=main.o Graph.o HBI.o
$(exe):$(obj)
	$(cc) -o $(exe) $(obj)
main.o: main.cpp HBI.h
	$(cc) -c main.cpp
Graph.o: Graph.cpp Graph.h BaseObj.h
	$(cc) -c Graph.cpp
HBI.o: HBI.cpp HBI.h Graph.h limit.h
	$(cc) -c HBI.cpp

.PYTHON:clean
clean:
	-rm -fr *.o