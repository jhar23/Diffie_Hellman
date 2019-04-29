#ifndef _DIFFIE_H
#define _DIFFIE_H
#include <vector>
#include <cmath>

using std::pow;
using std::vector;
/**
 * The purpose of Diffie is to contain important
 * functions for creating the secret key
 */
class Diffie{
public:
  Diffie();
  int getSecret();
  int getPrimeOne();
  void setPrivateKey(int key);
private:
  int createPrime();
  int createSecret();
  vector<int> primes;
  void _listPrimes();
  int primeOne;
  int secret;
  int privateKey;

};






#endif /* end of include guard: DIFFIE */
