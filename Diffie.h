#ifndef _DIFFIE_H
#define _DIFFIE_H
#include <vector>
#include <cmath>

using std::vector;
/**
 * The purpose of Diffie is to contain important
 * functions for creating the secret key
 */
class Diffie{
public:
  int createPrime();
  int createSender(int key, int keyOne);
private:
  vector<int> primes;
  void _listPrimes();

};






#endif /* end of include guard: DIFFIE */
