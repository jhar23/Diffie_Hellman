#include "Server.h"

void createHostKey(Diffie& host){
  int status, socketfd, accept_socket, buffer, yes = 1;
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
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

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

  int modval = htonl(host.getModuloValue());
  bytes_sent = send(accept_socket, &modval, sizeof(int32_t), 0);


  recv(accept_socket, &buffer, sizeof(int32_t), 0);
  host.setCrossoverValue(ntohl(buffer));

  int crossVal;
  crossVal = htonl(host.createCrossoverValue());
  bytes_sent = send(accept_socket, &crossVal, sizeof(int32_t), 0);


  std::cout << "this should be same: " << host.createPrivateKey() << std::endl;

  close(socketfd);
  close(accept_socket);
  return;
}
