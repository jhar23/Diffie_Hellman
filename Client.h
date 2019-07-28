#ifndef _CLIENT_
#define _CLIENT_
#include "Diffie.h"
#include "Chat.h"


void createClientKey();

int connectToServer();

int establishClientKey(int socketfd);

void clientChat(int socketfd, int key);

void client_recv_loop(int socketfd, int key);

void client_send_loop(int socketfd, int key);



#endif
