GCC=gcc -Wall -Wextra -pedantic


all: server client

run: all
	./server 8888 &
	./client 8888
	exit

server:
	$(GCC) server.c utils.c -o server
client:
	$(GCC) client.c utils.c -o client

clean:
	rm -f *.o server client