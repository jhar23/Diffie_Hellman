#include "Server.h"

void buildServer(){
  std::cout << "Calling Build Server..." << std::endl;
  int status, socketfd, accept_socket;
  int opt = 1;
  socklen_t addr_size;
  struct addrinfo hints, *res;
  struct sockaddr_storage their_addr;
  addr_size = sizeof(their_addr);

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
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  if(bind(socketfd, res->ai_addr, res->ai_addrlen) == -1){
    fprintf(stderr, "socket binding error");
    exit(1);
  }
  free(res);
  listen(socketfd, 10);
  std::cout << "Listening..." << std::endl;


  accept_socket = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);

  std::cout << "I got something" << std::endl;

  const char *hello = "Hello Person";
  int len, bytes_sent;
  len = strlen(hello);
  bytes_sent = send(accept_socket, hello, len, 0);
  std::cout << bytes_sent << "Bytes sent" << std::endl;

  close(socketfd);
  close(accept_socket);
  return;
}
