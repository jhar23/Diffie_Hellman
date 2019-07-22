#include "Diffie.h"



Diffie::Diffie()
{
  srand(time(NULL));
  _listPrimes();
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
    for(int i=3; i < 75; i++){
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

int Diffie::getPrivateKey()
{
  return privateKey;
}

void Diffie::setPrivateKey(int key)
{
  privateKey = key;
}

void Diffie::setModuloValue(int key)
{
  moduloValue = key;
}

void Diffie::setCrossoverValue(int key){
  crossoverValue = key;
}

int Diffie::createPrivateKey()
{
  privateKey = ((int)pow(crossoverValue, secretPower) % moduloValue);
  return privateKey;
}

int Diffie::createCrossoverValue()
{
  return ((int)pow(baseNumber, secretPower) % moduloValue);
}

int Diffie::getSecret()
{
  return secretPower;
}

int Diffie::getBaseNumber()
{
  return baseNumber;
}

int Diffie::getModuloValue()
{
  return moduloValue;
}

void Diffie::setBaseNumber(int key)
{
  baseNumber = key;
}

int Diffie::setPrime()
{
  return (primes[rand() % primes.size()]);
}

int Diffie::setSecret()
{
  int secret = ((rand() % 4) + 2);
  return secret;

}
