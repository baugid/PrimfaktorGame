#pragma once
#include "GameDifficulty.h"
class Factorization
{
private:
	unsigned long* primes;
	unsigned long solution;
	const GameDifficulty* dif;
public:
	explicit Factorization(const GameDifficulty *d);
	~Factorization();
	unsigned long primesLength;
	unsigned long genTask();
	bool checkFactorization(const unsigned long* p, unsigned long length) const;
	const unsigned long* getPrimes() const;
};

