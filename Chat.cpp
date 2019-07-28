#include "Chat.h"

void recv_loop(int socketfd, int key)
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

void send_loop(int socketfd, int key)
{
  char buffer[32];
  int conn = 1;
  std::cin.ignore(0, '\n');
  while(true)
  {
    memset(buffer, 0, sizeof(buffer));

    std::cout << "Send a message: ";

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
