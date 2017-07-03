#include "factorization.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>

Factorization::Factorization(GameDifficulty* d)
{
	dif = d;
}

Factorization::~Factorization()
{
	delete[] primes;
}

unsigned long Factorization::genTask()
{
	srand(time(NULL));
	unsigned long product = 1;
	primesLength = (rand() % dif->getMaxNumbers()) + 1; //calc length of the array
	delete[] primes;
	primes = new unsigned long[primesLength];
	for (unsigned long i = 0; i < primesLength; i++) { //calc primes
		primes[i] = dif->getAllPrimes()[rand() % dif->getAmountOfPrimes()];
	}
	for (unsigned long i = 0; i < primesLength; i++) {
		product *= primes[i];
	}
	solution = product;
	return product;
}

bool Factorization::checkFactorization(const unsigned long * p, unsigned long length) const
{
	if (length != primesLength) // check lengths
		return false;
	unsigned long product=1;	//check products
	for (unsigned long i = 0; i < primesLength; i++) {
		product *= primes[i];
	}
	if (product != solution) {
		return false;
	}
	bool isPrime;
	for (unsigned long i = 0; i < primesLength; i++) { //check if numbers are prime
		isPrime = false;
		std::for_each(dif->getAllPrimes(), &dif->getAllPrimes()[dif->getAmountOfPrimes()], [&](unsigned long prime)->void {
			if (prime == p[i]) { isPrime = true;}
		});
		if (isPrime == false) {
			return false;
		}
	}
	return true;
}

const unsigned long * Factorization::getPrimes() const
{
	return primes;
}

