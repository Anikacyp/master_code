cc=g++
exe=main
obj=main.o Graph.o
$(exe):$(obj)
	$(cc) -o $(exe) $(obj)
main.o: main.cpp Graph.h
	$(cc) -c main.cpp
Graph.o: Graph.cpp Graph.h BaseObj.h
	$(cc) -c Graph.cpp

.PYTHON:clean
clean:
	-rm -fr *.o