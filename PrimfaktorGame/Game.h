#pragma once
#include "GameDifficulty.h"
#include "factorization.h"
class Game
{
private:
	GameDifficulty *dif;
	int currentPrimeProgress;
	int currentNumbersProgress;
	const int lvlUpPrimes;
	const double numberUpTime;
	const int lvlUpNumbs;
	Factorization *task;
public:
	~Game();
	explicit Game(int PrimeUpDifficulty = 5, double speedLimit = 15.0, int NumberUpDifficulty = 3);
	void init();
	void run();
};

