#include "Chat.h"

void recv_loop(int socketfd, int key)
{
  // char buffer[32] is the buffer for input
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
      // "Decrypt" XOR cipher
      buffer[i] = buffer[i] ^ key;
    }

    printf("\nMessage Received: %s\n", buffer);
  }
}

void send_loop(int socketfd, int key)
{
  char buffer[32];
  int conn = 1;
  // Ignore first newline to get cin to work correctly
  // Bugged as of right now...
  std::cin.ignore(0, '\n');
  while(true)
  {
    // reset buffer
    memset(buffer, 0, sizeof(buffer));

    std::cout << "Send a message: ";

    std::cin.getline(buffer, sizeof(buffer));

    // close when input is "exit"
    if(strcmp(buffer, "exit") == 0)
    {
      close(socketfd);
      break;
    }

    for(unsigned long i = 0; i < strlen(buffer); i++)
    {
      // "Encrypt" with XOR Cipher
      buffer[i] = key ^ buffer[i];
    }
    conn = send(socketfd, &buffer, strlen(buffer), 0);
    if(conn == -1)
    {
      // break if connection is lost
      break;
    }
  }
}
