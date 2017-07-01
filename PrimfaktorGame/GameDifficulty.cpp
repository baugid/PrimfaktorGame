#include "GameDifficulty.h"
#include <math.h>
#include <fstream>
#include <vector>
#include <algorithm>
//Fileformat : 4Bytes MaxPrime 4Bytes MaxNumbers
bool GameDifficulty::checkPrime(const long p)
{
	if (p == 2 || p == 3|| p==5) {
		return true;
	}
	if (!(p % 2) || !(p % 3) || p <= 1) { //checks p<1 or divided by 2/3
		return false;
	}
	long sqrt = sqrtl(p);
	for (long i = 5; i < sqrt; i += 4) { //tests all numbers n>=5 n=6k+-1 
		if (!(p%i)) {
			return false;
		}
		i += 2;
		if (!(p%i)) {
			return false;
		}
	}
	return true;
}

void GameDifficulty::genAllPrimes()
{
	bool divisible1 = false;
	bool divisible2 = false;
	std::vector<long> prime;
	prime.push_back(2);
	prime.push_back(3);
	for (long i = 5; i < maxPrime; i += 6) { // check all numbers from 5 to maxPrime if they are prime
		std::for_each(prime.begin(), prime.end(), [&](long t)->void { // if i or i+2 divisible by one of prime flag that
			if (!(i%t)) { divisible1 = true; }
			if (!((i + 2) % t)) { divisible2 = true; }
		});
		if (divisible1) {	// interpret the flags
			divisible1 = false;
		}
		else {
			prime.push_back(i);
		}
		if (i + 2 == maxPrime) {
			break;
		}
		if (divisible2) {
			divisible2 = false;
		}
		else {
			prime.push_back(i + 2);
		}
	}
	prime.push_back(maxPrime);
	delete[] primes;								// puts the primes in an array
	amountOfPrimes = prime.size();
	primes = new long[amountOfPrimes];
	for (long i = 0; i < amountOfPrimes; i++) {
		primes[i] = prime.at(i);
	}
}

GameDifficulty::GameDifficulty() // gens basic difficulty;
{
	saveFile = "GameSave.bin";
	maxNumbers = 3;
	maxPrime = 7;
	genAllPrimes();
}

GameDifficulty::~GameDifficulty() //default destructor
{
	delete[] saveFile;
	delete[] primes;
}

GameDifficulty::GameDifficulty(long maxP, long maxN) : maxPrime(maxP), maxNumbers(maxN) // Difficulty based on params min is base difficulty 
{
	saveFile = "GameSave.bin";
	if (!checkPrime(maxPrime)) {
		maxPrime = 7;
	}
	if (maxNumbers < 3) {
		maxNumbers = 3;
	}
	genAllPrimes();
}

GameDifficulty::GameDifficulty(const char * filename) //create based on file
{
	if (filename == nullptr) {
		saveFile = "GameSave.bin";
	}
	saveFile = filename;
	std::ifstream in;
	char* buffer = new char[sizeof(long)];
	bool saveCorrected = false;
	in.open(saveFile, std::ios::in | std::ios::binary);
	if (!in) {
		maxPrime = 7;
		maxNumbers = 3;
	}
	if (in.eof()) {	//if file is empty use and save defaults
		maxPrime = 7;
		maxNumbers = 3;
		genAllPrimes();
		in.close();
		saveCorrected = true;
	}
	else { //load file and check if those values are correct
		in.read(buffer, sizeof(long));
		maxPrime = std::atol(buffer);
		in.read(buffer, sizeof(long));
		maxNumbers = std::atol(buffer);
		in.close();
		if (!checkPrime(maxPrime)) {
			maxPrime = 7;
			saveCorrected = true;
		}
		if (maxNumbers < 3) {
			maxNumbers = 3;
			saveCorrected = true;;
		}
	}
	genAllPrimes();
	if (saveCorrected) {
		saveState(saveFile);
	}
	delete[] buffer;
}




long GameDifficulty::getMaxPrime()
{
	return maxPrime;
}

bool GameDifficulty::setMaxPrime(long p) //sets maxPrime checks if it´s a prime number
{
	if (checkPrime(p)) {
		maxPrime = p;
		genAllPrimes();
		saveState(saveFile);
		return true;
	}
	return false;
}

void GameDifficulty::setMaxNumbers(long n)
{
	if (n >= 3) {
		maxNumbers = n;
		saveState(saveFile);
	}
}

long GameDifficulty::getMaxNumbers()
{
	return maxNumbers;
}

const long* GameDifficulty::getAllPrimes()
{
	return primes;
}

long GameDifficulty::getAmountOfPrimes()
{
	return amountOfPrimes;
}

void GameDifficulty::saveState(const char * filename)
{
	std::ofstream out;
	out.open(filename, std::ios::out | std::ios::binary);
	if (out) {
		out.write((char*)&maxPrime, sizeof(long)); // save maxPrime
		out.write((char*)&maxNumbers, sizeof(long)); // save maxNumbers
	}
	out.close();
}

void GameDifficulty::setSaveFile(const char * filename)
{
	delete[] saveFile;
	saveFile = filename;
}

void GameDifficulty::increaseMaxPrime() // update maxPrime
{
	long newPrime = maxPrime + 2;
	while (!checkPrime(newPrime)) {
		newPrime += 2;
	}
	maxPrime = newPrime;
	genAllPrimes();
	saveState(saveFile);
}
