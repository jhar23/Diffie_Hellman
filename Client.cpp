#include "Client.h"

void runClient(Diffie& client){
  int status, socketfd;

  int base = client.getBaseNumber();
  std::cout << base << std::endl;
  struct addrinfo hints, *res;
  int buffer;
  memset(&buffer, 0, sizeof(buffer));
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

  int bytes_recv;
  bytes_recv = recv(socketfd, &buffer, sizeof(int32_t), 0);
  int returnVal = htonl(333);
  std::cout << "Val: " << ntohl(returnVal) << std::endl;
  send(socketfd, &returnVal, sizeof(int32_t), 0);
  if(bytes_recv != sizeof(int32_t)){
    fprintf(stderr, "stream error");
    exit(1);
  }

  client.setCrossoverValue(ntohl(buffer));

/*
int hostSocket;
memset(&hints, 0, sizeof(hints));
if((status = getaddrinfo("127.0.0.1, 8001", &hints, &res)) != 0){
  fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
  exit(1);
}

if((hostSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
  fprintf(stderr, "socket error");
  exit(1);
}

if(bind(socketfd, res->ai_addr, res->ai_addrlen) == -1){
  fprintf(stderr, "socket binding error");
  exit(1);
}
*/

  free(res);
  close(socketfd);
  return;
}
