#include "Diffie.h"

Diffie::Diffie(){
  primeOne = createPrime();
  secret = createSecret();
}

void Diffie::_listPrimes(){
  vector<int> primestemp;
  primestemp.push_back(2);
    for(int i=3; i < 100; i++){
      bool prime=true;
      for(unsigned j=0;j<primestemp.size() && primestemp[j]*primestemp[j] <= i;j++){
          if(i % primestemp[j] == 0){
            prime=false;
            break;
          }
      }
      if(prime)
        primes.push_back(i);
    }
}

void setPrivateKey(int key){
  privateKey = key;
}

int Diffie::getSecret(){
  return secret;
}

int Diffie::getPrimeOne(){
  return primeOne;
}

int Diffie::createPrime(){
  _listPrimes();
  return (primes[rand() % primes.size()]);
}

int Diffie::createSecret(){
  int secret = rand() % 25;
  return secret;

}
