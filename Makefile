CFLAGS=-I. -pthread -std=c99
# DEPS=list.h



all: server client

server: server.c list.h
	gcc -o server server.c list.c $(CFLAGS)

client: client.c
	gcc -o client client.c $(CFLAGS)

# %: %.c $(DEPS)
# 	$(CC) -o $@ $< $(CFLAGS)