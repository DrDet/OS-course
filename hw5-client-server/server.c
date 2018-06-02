#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "utils.h"

#define MAX_REQUESTS_QUEUE (100)

void* make_reply(char* buf, int len, char* dst, int* len_dst) {
	char* prefix = "Hello, ";
	memcpy(dst, prefix, strlen(prefix));
	memcpy(&dst[strlen(prefix)], buf, len);
	*len_dst = strlen(prefix) + len;
	dst[(*len_dst)++] = NULL;
	return dst;
}

int main(int argc, char* argv[]) {
	check(argc, 2, 1, "Expected 1 argument.\nUsage: server <port>");
	int port = htons(atoi(argv[1]));
	uint32_t ip = htonl(INADDR_LOOPBACK);
	int lstn_sock = socket(AF_INET, SOCK_STREAM, 0);
	check(lstn_sock, -1, 0, "Error occurred during socket creation");
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = ip;
	check(bind(lstn_sock, (struct sockaddr *) &addr, sizeof(addr)), 0, 1, "Couldn't bind to the given port");
	check(listen(lstn_sock, MAX_REQUESTS_QUEUE), 0, 1, "Couldn't listen socket");
	while (1) {
		printf("Server: waiting for request...\n");
		int client_sock = accept(lstn_sock, NULL, NULL);
		check(client_sock, -1, 0, "Couldn't accept connection");
		char buf[1024];
		char reply[1024];
		while (1) {
			int cnt = recv(client_sock, buf, 1024, 0);
			check(cnt, -1, 0, "Error during receiving");
			if (cnt == 0) {
				break;
			}
			printf("Server: received a request: %s\n", buf);
			int len;
			make_reply(buf, cnt, reply, &len);
			printf("Server: processed\n");
			send(client_sock, reply, len, 0);	
		}
	}
	return 0;
}