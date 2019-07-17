#include "Client.h"

void createClientKey(){
  int socketfd = connectToServer();
  std::cout << "These should be the same: " << establishClientKey(socketfd) << std::endl;

}

int establishClientKey(int socketfd)
{
  Diffie client;
  int buffer, bytes_recv;

  bytes_recv = recv(socketfd, &buffer, sizeof(int32_t), 0);
  client.setBaseNumber(ntohl(buffer));


  bytes_recv = recv(socketfd, &buffer, sizeof(int32_t), 0);
  client.setModuloValue(ntohl(buffer));


  int crossVal = htonl(client.createCrossoverValue());
  send(socketfd, &crossVal, sizeof(int32_t), 0);

  bytes_recv = recv(socketfd, &buffer, sizeof(int32_t), 0);
  client.setCrossoverValue(ntohl(buffer));


  close(socketfd);
  return client.createPrivateKey();
}

int connectToServer()
{
  int status, socketfd;

  struct addrinfo hints, *res;
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

  connect(socketfd, res->ai_addr, res->ai_addrlen);
  free(res);

  return socketfd;
}
