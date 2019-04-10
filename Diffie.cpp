#include "diffie.h"

int main(){
  return 0;
}

void Diffie::_listPrimes(){
  vector<int> primestemp;
  primestemp.push_back(2);
    for(int i=3; i < 200; i++){
      bool prime=true;
      for(int j=0;j<primestemp.size() && primestemp[j]*primestemp[j] <= i;j++){
          if(i % primestemp[j] == 0){
            prime=false;
            break;
          }
      }
      if(prime)
        primes.push_back(i);
    }
}

int Diffie::createPrime(){
  listPrimes();
  return (primes[rand() % primes.size()]);
}

int Diffie::createSender(int key int keyOne);
