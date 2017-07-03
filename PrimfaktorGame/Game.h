#pragma once
#include "GameDifficulty.h"
#include "factorization.h"
#include <string>
class Game
{
private:
	GameDifficulty *dif;
	int currentPrimeProgress;
	int currentNumbersProgress;
	int currentPrimeDownProgress;
	int currentNumbersDownProgress;
	const int lvlUpPrimes;
	const long numberUpTime;
	const int lvlUpNumbs;
	const int lvlDownPrimes;
	const long numberDownTime;
	const int lvlDownNumbs;
	Factorization *task;
	const unsigned long* castInput(const std::string s, unsigned long& length);
	void calcNewLevels();
public:
	~Game();
	explicit Game(int primeUpDifficulty = 5, long speedLimit = 15, int numberUpDifficulty = 3, int primeDownDifficulty = 4,long slowLimit = 45 , int numberDownDifficulty = 3);
	void init();
	void run();
};

