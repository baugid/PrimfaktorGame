#include "factorization.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>

Factorization::Factorization(const GameDifficulty* d)
{
	dif = const_cast<GameDifficulty*>(d);
}

Factorization::~Factorization()
{
	delete[] primes;
}

long Factorization::genTask()
{
	srand(time(NULL));
	long product = 1;
	primesLength = (rand() % dif->getMaxNumbers()) + 1; //calc length of the array
	delete[] primes;
	primes = new long[primesLength];
	for (long i = 0; i < primesLength; i++) { //calc primes
		primes[i] = dif->getAllPrimes()[rand() % dif->getAmountOfPrimes()];
	}
	for (long i = 0; i < primesLength; i++) { 
		product *= primes[i];
	}
	solution = product;
	return product;
}

bool Factorization::checkFactorization(const long * p, int length)
{
	if (length != primesLength) // check lengths
		return false;
	long product=1;	//check products
	for (long i = 0; i < primesLength; i++) {
		product *= primes[i];
	}
	if (product != solution) {
		return false;
	}
	bool isPrime;
	for (long i = 0; i < primesLength; i++) { //check if numbers are prime
		isPrime = false;
		std::for_each(dif->getAllPrimes(), &dif->getAllPrimes()[dif->getAmountOfPrimes()], [&](long prime)->void { 
			if (prime == p[i]) { isPrime = true;}
		});
		if (isPrime == false) {
			return false;
		}
	}
	return true;
}

const long * Factorization::getPrimes()
{
	return primes;
}

