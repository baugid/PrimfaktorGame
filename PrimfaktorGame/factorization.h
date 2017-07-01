#pragma once
#include "GameDifficulty.h"
class Factorization
{
private:
	long* primes;
	long solution;
public:
	explicit Factorization(const GameDifficulty *d);
	~Factorization();
	GameDifficulty* dif;
	long primesLength;
	long genTask();
	bool checkFactorization(const long* p, int length);
	const long* getPrimes();
};

