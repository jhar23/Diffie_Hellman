#ifndef _MAIN_
#define _MAIN_
#include "Server.h"
#include "Client.h"
#include "Diffie.h"

int main(int argc, char const *argv[]){
  Diffie alice;

  if (argc != 2) {
    fprintf(stderr,"usage: Diffie [hostname or \"Host\"]\n");
    return 1;
  }
  if(strcmp(argv[1],"host") == 0){

    createHostKey(alice);
  }
  if(strcmp(argv[1],"client") == 0){

    createClientKey(alice);
  }
  else{

  }
  return 0;
}
#endif
