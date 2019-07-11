#ifndef _MAIN_
#define _MAIN_
#include "Diffie.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>



int main(int argc, char const *argv[]){
  Diffie alice;
  int status, socketfd, accsocket;
  socklen_t addr_size;
  struct addrinfo hints;
  struct sockaddr_storage their_addr;
  struct addrinfo* res;

  if (argc < 2) {
    fprintf(stderr,"usage: Diffie [hostname] [listen]\n");
    return 1;
  }

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if((status = getaddrinfo(argv[1], "5000", &hints, &res)) != 0){
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  if((socketfd = socket(res->ai_family, res->ai_socktype, 0)) == -1){
    fprintf(stderr, "socket connecting error");
    exit(1);
  }

  bind(socketfd, res->ai_addr, res->ai_addrlen);

  listen(socketfd, 10);

  addr_size = sizeof(their_addr);
  accsocket = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);

//connect(socketfd, res->ai_addr, res->ai_addrlen);
free(res);
}
#endif
