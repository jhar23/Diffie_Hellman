#include "Client.h"

// createClientKey guides the client to chat
void createClientKey(){

  // int socketfd is our client socket descriptor
  int socketfd = connectToServer();

  // int key is our public key
  int key = establishClientKey(socketfd);

  std::cout << "These should be the same: " << key << std::endl;

  clientChat(socketfd, key);
  std::cout << "Chat Terminated" << std::endl;
}

int connectToServer()
{
  int status, socketfd;
  struct addrinfo hints, *res;

  // set hints to 0
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET; // IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP
  hints.ai_flags = AI_PASSIVE;

  // string host is the IP address
  std::string host;
  std::cout << "What address do you want to connect to? " << std::endl;
  std::cin >> host;

  // Get host IP, port 8000
  if((status = getaddrinfo(host.c_str(), "8000", &hints, &res)) != 0){
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  // Initialize socket descriptor
  if((socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
    fprintf(stderr, "socket error");
    exit(1);
  }

  // Connect socket to host
  connect(socketfd, res->ai_addr, res->ai_addrlen);
  free(res);

  return socketfd;
}

// Performs the Diffie-Hellman key exchange
// @return public key
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

  return client.createPrivateKey();
}

void clientChat(int socketfd, int key)
{
  // Thread for Chat's send_loop
  std::thread send(send_loop, socketfd, key);

  // Thread for Chat's recv_loop
  std::thread recv(recv_loop, socketfd, key);

  // Join threads
  send.join();
  recv.join();

}
