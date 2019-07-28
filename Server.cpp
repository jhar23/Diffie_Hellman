#include "Server.h"


void createHostKey(){

  int accept_socket, socketfd;
  socklen_t addr_size;
  struct sockaddr_storage their_addr;
  addr_size = sizeof(their_addr);

  socketfd = bindSocket();

  listen(socketfd, 10);
  accept_socket = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);

  int key = establishHostKey(accept_socket);
  std::cout << "This should be the same: " << key << std::endl;

  serverChat(accept_socket, key);

  close(socketfd);
  std::cout << "Chat Terminated" << std::endl;
}

int establishHostKey(int accept_socket)
{
  Diffie host;
  int buffer;



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

  return host.createPrivateKey();
}

int bindSocket()
{
  int status, socketfd, yes = 1;

  struct addrinfo hints, *res;


  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET; // IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP
  hints.ai_flags = AI_PASSIVE;

  if((status = getaddrinfo(NULL, "8000", &hints, &res)) != 0){
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  if((socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
    fprintf(stderr, "socket error");
    exit(1);
  }
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

  if(bind(socketfd, res->ai_addr, res->ai_addrlen) == -1){
    fprintf(stderr, "socket binding error: %s\n", strerror(errno));
    exit(1);
  }

  free(res);
  return socketfd;
}

void serverChat(int accept_socket, int key)
{
  std::thread send (send_loop, accept_socket, key);
  std::thread recv (recv_loop, accept_socket, key);

  send.join();
  recv.join();
}
