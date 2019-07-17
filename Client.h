#ifndef _CLIENT_
#define _CLIENT_
#include "Diffie.h"
#include <cerrno>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void createClientKey(Diffie& client);



#endif
