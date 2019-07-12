#include "Server.h"

void buildServer(Diffie& host){
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

  accept_socket = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);


  int base = htonl(host.getBaseNumber());
  int bytes_sent;
  bytes_sent = send(accept_socket, &base, sizeof(int32_t), 0);

  int buffer;
  recv(accept_socket, &buffer, sizeof(int32_t), 0);
  int data = ntohl(buffer);
  std::cout << "this is data" << data << std::endl;

  close(socketfd);
  close(accept_socket);
  return;
}
