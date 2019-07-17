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

  void createHostKey();

  int bindSocket();

  int establishHostKey(int socketfd);



#endif
