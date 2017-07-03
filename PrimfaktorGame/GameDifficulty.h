#pragma once
class GameDifficulty
{
private:
	unsigned long maxPrime;
	unsigned long maxNumbers;
	bool checkPrime(unsigned long p);
	unsigned long* primes;
	const char* saveFile;
	unsigned long amountOfPrimes;
	void genAllPrimes();
	union longchar {
		char chars[sizeof(unsigned long)];
		unsigned long out;
	};
public:
	explicit GameDifficulty();
	~GameDifficulty();
	explicit GameDifficulty(unsigned long maxP, unsigned long maxN);
	explicit GameDifficulty(const char* filename);
	unsigned long getMaxPrime() const;
	bool setMaxPrime(unsigned long p);
	void setMaxNumbers(unsigned long n);
	unsigned long getMaxNumbers() const;
	const unsigned long* getAllPrimes() const;
	unsigned long getAmountOfPrimes() const;
	void saveState(const char * filename) const;
	void setSaveFile(const char *filename);
	void increaseMaxPrime();
};

