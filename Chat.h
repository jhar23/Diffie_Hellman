#ifndef _CHAT_
#define _CHAT_
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

  void recv_loop(int socketfd, int key);
  
  void send_loop(int socketfd, int key);

#endif
