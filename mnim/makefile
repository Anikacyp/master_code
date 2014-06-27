cc=g++
exe=main
obj=main.o Graph.o Model.o Seed.o Heap.o
$(exe):$(obj)
	$(cc) -o $(exe) $(obj)
main.o: main.cpp Model.h
	$(cc) -c main.cpp
Graph.o: Graph.cpp Graph.h BaseObj.h
	$(cc) -c Graph.cpp
Model.o: Model.cpp Model.h Graph.h limit.h
	$(cc) -c Model.cpp
Seed.o: Seed.cpp Seed.h Model.h BaseObj.h Heap.h
	$(cc) -c Seed.cpp
Heap.o: Heap.cpp Heap.h
	$(cc) -c Heap.cpp
.PYTHON:clean
clean:
	-rm -fr *.o