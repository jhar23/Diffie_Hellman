#include "Diffie.h"

Diffie::Diffie()
{
  baseNumber = setPrime();
  moduloValue = setPrime();
  secretPower = setSecret();
  privateKey = -1;
  crossoverValue = -1;
}

void Diffie::_listPrimes()
{
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

void Diffie::setPrivateKey(int key)
{
  privateKey.store(key, std::memory_order_relaxed);
}

void Diffie::setCrossoverValue(int key){
  crossoverValue.store(key, std::memory_order_relaxed);
}

int Diffie::getSecret()
{
  return secretPower.load(std::memory_order_relaxed);
}

int Diffie::getBaseNumber()
{
  return baseNumber.load(std::memory_order_relaxed);
}

int Diffie::setPrime()
{
  _listPrimes();
  return (primes[rand() % primes.size()]);
}

int Diffie::setSecret()
{
  int secret = rand() % 25;
  return secret;

}
