#pragma once
#include "GameDifficulty.h"
class Factorization
{
private:
	unsigned long* primes;
	unsigned long solution;
public:
	explicit Factorization(GameDifficulty *d);
	~Factorization();
	GameDifficulty* dif;
	unsigned long primesLength;
	unsigned long genTask();
	bool checkFactorization(const unsigned long* p, unsigned long length) const;
	const unsigned long* getPrimes() const;
};

