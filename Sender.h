#ifndef _SENDER_H
#define _SENDER_H

#include "Diffie.h"

class Sender{
public:
  void sendto();
  
private:
  Diffie sender;
  int createPrivateKey();



};



#endif
