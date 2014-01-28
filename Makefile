OBJS = mst.o fibonacciheap.o fheapNode.o
CC = g++
DEBUG = -g
CFLAGS =  -c $(DEBUG)
LFLAGS =  $(DEBUG)

mst : $(OBJS)
	    $(CC) $(LFLAGS) $(OBJS) -o mst

fibonacciheap.o : fibonacciheap.h fibonacciheap.cpp fheapNode.h
		$(CC) $(CFLAGS) fibonacciheap.cpp

fheapNode.o : fheapNode.h fheapNode.cpp		
		$(CC) $(CFLAGS) fheapNode.cpp

clean:
	    \rm *.o mst

