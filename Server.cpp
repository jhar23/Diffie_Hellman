#include "Server.h"

// createHostKey guides the client to chat.
void createHostKey(){

  int accept_socket, socketfd;
  socklen_t addr_size;
  struct sockaddr_storage their_addr;
  addr_size = sizeof(their_addr);

  // int socketfd is our host socket descriptor
  socketfd = bindSocket();

  listen(socketfd, 10);

  // int accept_socket is the client socket descriptor
  accept_socket = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);

  // int key is our public key
  int key = establishHostKey(accept_socket);
  std::cout << "This should be the same: " << key << std::endl;

  serverChat(accept_socket, key);

  close(socketfd);
  std::cout << "Chat Terminated" << std::endl;
}

// Performs the Diffie-Hellman key exchange
// @return public key
int establishHostKey(int accept_socket)
{
  Diffie host;
  int buffer, bytes_sent;

  // htonl == host to network long, for sending ints over TCP
  int base = htonl(host.getBaseNumber());
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
// Bind socket to port 8000
// @return host socket descriptor
int bindSocket()
{
  int status, socketfd, yes = 1;

  struct addrinfo hints, *res;

  // Set hints to 0
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET; // IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP
  hints.ai_flags = AI_PASSIVE;

  // Get any localhost IP, port 8000
  if((status = getaddrinfo(NULL, "8000", &hints, &res)) != 0){
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }
  // Initialize socket descriptor
  if((socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
    fprintf(stderr, "socket error");
    exit(1);
  }

  // Set socket option to reuse port after closing
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

  // Bind socket to port
  if(bind(socketfd, res->ai_addr, res->ai_addrlen) == -1){
    fprintf(stderr, "socket binding error: %s\n", strerror(errno));
    exit(1);
  }

  free(res); // Free addrinfo, as it is not used
  return socketfd;
}

void serverChat(int accept_socket, int key)
{
  // Thread for Chat's send_loop
  std::thread send (send_loop, accept_socket, key);

  // Thread for Chat's recv_loop
  std::thread recv (recv_loop, accept_socket, key);

  // Join threads
  send.join();
  recv.join();
}
