#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>

int socket_custom(char* port);
int discover(int sock);
int send_packet(void* buffer, int buffer_size, int sock, struct sockaddr_in *dest);



#endif // SOCKET_H