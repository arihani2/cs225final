CC = g++
CFLAGS  = -g -Wall

main: code/edge.h code/graph.h
	$(CC) $(CFLAGS) -o main code/edge.h code/graph.h -I.