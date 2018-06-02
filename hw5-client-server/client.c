#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "utils.h"

int main(int argc, char* argv[]) {
	check(argc, 2, 1, "Expected 1 argument.\nUsage: client <port>");
	int port = htons(atoi(argv[1]));
	uint32_t ip = htonl(INADDR_LOOPBACK);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = ip;
	check(connect(sock, (struct sockaddr *)&addr, sizeof(addr)), -1, 0, "Couldn't connect");
	char buf[1024];
	for (int i = 0; i < 10; ++i) {
		char pref[10] = "Dima ";
		char dig[2];
		dig[0] = '0' + i;
		dig[1] = NULL;
		char* msg = strcat(pref, dig);
		printf("Client: send request: %s\n", msg);
		send(sock, msg, strlen(msg), 0);
		recv(sock, buf, 1024, 0);
		printf("Client: received response: %s\n", buf);
	}
	close(sock);
	printf("Client ended\n");
	return 0;
}