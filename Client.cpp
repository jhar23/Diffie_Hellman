#include "Client.h"

void createClientKey(){

  int socketfd = connectToServer();
  int key = establishClientKey(socketfd);

  std::cout << "These should be the same: " << key << std::endl;

  clientChat(socketfd, key);

}

int connectToServer()
{
  int status, socketfd;
  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET; // IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP
  hints.ai_flags = AI_PASSIVE;

  std::string host;
  std::cout << "What address do you want to connect to? " << std::endl;
  std::cin >> host;

  if((status = getaddrinfo(host.c_str(), "8000", &hints, &res)) != 0){
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
  std::thread send(client_send_loop, socketfd, key);
  std::thread recv(client_recv_loop, socketfd, key);

  send.join();
  recv.join();

}

void client_recv_loop(int socketfd, int key)
{
  char buffer[32];
  while(true)
  {
    memset(&buffer, 0, sizeof(buffer));
    unsigned long bytes_recv;


    bytes_recv = recv(socketfd, &buffer, sizeof(buffer), 0);

    if(bytes_recv == 0)
    {
      break;
    }

    for(unsigned long i = 0; i < bytes_recv; i++)
    {
      buffer[i] = buffer[i] ^ key;
    }

    printf("\nMessage Received: %s\n", buffer);
  }
}

void client_send_loop(int socketfd, int key)
{
  char buffer[32];
  int conn = 1;
  std::cin.ignore();
  while(true)
  {
    memset(buffer, 0, sizeof(buffer));
    std::cout << "Send a message to host: ";

    std::cin.getline(buffer, sizeof(buffer));

    if(strcmp(buffer, "exit") == 0)
    {
      close(socketfd);
      break;
    }

    for(unsigned long i = 0; i < strlen(buffer); i++)
    {
      buffer[i] = key ^ buffer[i];
    }
    conn = send(socketfd, &buffer, strlen(buffer), 0);
    if(conn == -1)
    {
      break;
    }
  }
}
