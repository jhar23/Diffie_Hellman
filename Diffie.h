#ifndef _DIFFIE_H
#define _DIFFIE_H
#include <vector>
#include <cmath>

using std::pow;
using std::atomic;
using std::vector;
/**
 * The purpose of Diffie is to contain important
 * functions for creating the secret key
 *
 * Each diffie has a mutually agreed upon
 * Starting number, baseNumber. They will
 * send that to the other person, primeOne
 *
 */
class Diffie{
public:
  // Default Constructor
  Diffie();

  // @return secretPower
  int getSecret();

  // @return baseNumber
  int getBaseNumber();

  /* Set the private key used to hash
   * @param key passes the key into privateKey
   */
  void setPrivateKey(int key);

  void setCrossoverValue(int key);


private:

  // @return prime number
  int setPrime();

  // @return secret number
  int setSecret();

  // Vector of all primes up to 100
  vector<int> primes;

  // Creates a list of all prime numbers to pull from
  void _listPrimes();

  // Mutually agreed upon number
  atomic<int> baseNumber;

  // Mutually agreed upon modulo
  atomic<int> moduloValue;

  // Secret Exponent
  atomic<int> secretPower;

  // Number received from other person
  atomic<int> crossoverValue;

  // Number after receiving both powers
  atomic<int> privateKey;

};






#endif /* end of include guard: DIFFIE */
