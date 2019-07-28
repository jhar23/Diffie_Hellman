#ifndef _CLIENT_
#define _CLIENT_
#include "Diffie.h"
#include "Chat.h"
#include <cerrno>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <thread>

void createClientKey();

int connectToServer();

int establishClientKey(int socketfd);

void clientChat(int socketfd, int key);

void client_recv_loop(int socketfd, int key);

void client_send_loop(int socketfd, int key);



#endif
