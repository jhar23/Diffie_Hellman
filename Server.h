#ifndef _SERVER_
#define _SERVER_
#include "Diffie.h"
#include "Chat.h"


  void createHostKey();

  int bindSocket();

  int establishHostKey(int accept_socket);

  void serverChat(int accept_socket, int key);



#endif
