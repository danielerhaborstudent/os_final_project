CFLAGS=-I. -pthread -std=c99

all: server client

server: server.c list.c
	gcc -o server server.c $(CFLAGS)

client: client.c
	gcc -o client client.c $(CFLAGS)