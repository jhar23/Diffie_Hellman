#ifndef _SERVER_
#define _SERVER_
#include "Diffie.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>

  void createHostKey();

  int bindSocket();

  int establishHostKey(int accept_socket);

  void serverChat(int accept_socket, int key);

  void server_recv_loop(int socketfd, int key);

  void server_send_loop(int socketfd, int key);



#endif
