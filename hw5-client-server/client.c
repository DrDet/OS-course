#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "utils.h"

int main(int argc, char* argv[]) {
	check(argc, 2, 1, "Expected 1 argument.\nUsage: server <port>");
	int port = htons(atoi(argv[1]));
	uint32_t ip = htonl(INADDR_LOOPBACK);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = ip;
	check(connect(sock, (struct sockaddr *)&addr, sizeof(addr)), -1, 0, "Couldn't connect");
	char msg[] = "World!";
	char buf[1024];
	send(sock, "World!", sizeof(msg), 0);
	int cnt = recv(sock, buf, 1024, 0);
	printf("%s\n", buf);
	close(sock);
	return 0;
}