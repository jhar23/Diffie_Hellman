#include "Client.h"

void runClient(){
  int status, socketfd;

  //int opt = 1;
  struct addrinfo hints, *res;
  char *buffer;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET; // IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP
  hints.ai_flags = AI_PASSIVE;

  if((status = getaddrinfo("127.0.0.1", "8000", &hints, &res)) != 0){
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  if((socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
    fprintf(stderr, "socket error");
    exit(1);
  }

  //setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));


  connect(socketfd, res->ai_addr, res->ai_addrlen);

  recv(socketfd, &buffer, 12, 0);
  std::cout << "Message Received: " << buffer << std::endl;
  free(res);
  close(socketfd);
  return;
}
