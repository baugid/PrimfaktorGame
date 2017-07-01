#pragma once
class GameDifficulty
{
private:
	long maxPrime;
	long maxNumbers;
	bool checkPrime(long p);
	long* primes;
	const char* saveFile;
	long amountOfPrimes;
	void genAllPrimes();
public:
	GameDifficulty();
	~GameDifficulty();
	GameDifficulty(long maxP, long maxN);
	explicit GameDifficulty(const char* filename);
	long getMaxPrime();
	bool setMaxPrime(long p);
	void setMaxNumbers(long n);
	long getMaxNumbers();
	const long* getAllPrimes();
	long getAmountOfPrimes();
	void saveState(const char * filename);
	void setSaveFile(const char *filename);
	void increaseMaxPrime();
};

