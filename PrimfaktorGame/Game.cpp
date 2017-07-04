#include "Game.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>

const unsigned long* Game::castInput(const std::string s, unsigned long& length)
{
	std::string buf;
	std::stringstream iss(s); //split string at " "
	std::vector<std::string> numbers;
	while (iss >> buf) {
		numbers.push_back(buf);
	}
	unsigned long* vals = new unsigned long[numbers.size()];	//convert string
	for (long i = 0; i < numbers.size(); i++) {
		vals[i] = std::atol(numbers.at(i).c_str());
	}
	length = numbers.size();
	return vals;
}

void Game::calcNewLevels()
{
	if (currentPrimeProgress == lvlUpPrimes) { //Prime lvl up
		dif->increaseMaxPrime();
		currentPrimeProgress = 0;
	}
	if (currentNumbersProgress == lvlUpNumbs) { //Numbers lvl up
		dif->setMaxNumbers(dif->getMaxNumbers() + 1);
		currentNumbersProgress = 0;
	}
	if (currentNumbersDownProgress == lvlDownNumbs) { //Numbers lvl down
		if (dif->getMaxNumbers() > 3) {
			dif->setMaxNumbers(dif->getMaxNumbers() - 1);
		}
			currentNumbersDownProgress = 0;
	}
	if (currentPrimeDownProgress == lvlDownPrimes) { //Prime lvl down
		if(dif->getMaxPrime()>7){
			dif->setMaxPrime(dif->getAllPrimes()[dif->getAmountOfPrimes() - 2]);
		}
			currentPrimeDownProgress = 0;
	}
}

Game::~Game()
{
	delete dif;
	delete task;
}

Game::Game(int primeUpDifficulty, long speedLimit, int numberUpDifficulty, int primeDownDifficulty, long slowLimit, int numberDownDifficulty) : lvlUpPrimes(primeUpDifficulty), numberUpTime(speedLimit), lvlUpNumbs(numberUpDifficulty), lvlDownPrimes(primeDownDifficulty), numberDownTime(slowLimit), lvlDownNumbs(numberDownDifficulty)
{
}

void Game::init()
{
	std::cout << "Hallo!\nHier darfst du Zahlen in ihre Primfaktoren zerlegen.\nGib die Primzahlen einfach mit Leerzeichen getrennt ein.\nBitte gib den Dateinamen des Spielstandes an (Falls du keinen hast einfach direkt Enter benutzen): ";
	std::string s;
	std::getline(std::cin, s);
	if (s == "") {
		dif = new GameDifficulty;
	}
	else {
		if (s.substr(s.find_last_of(".") + 1) != "bin") { // checks if the file has the .bin ending
			s.append(".bin");
			dif = new GameDifficulty(s.c_str());
		}
		else {
			dif = new GameDifficulty(s.c_str());
		}
	}
	task = new Factorization(dif);
	std::cout << "Deine Datei wurde geladen!\nEs geht gleich los!\n";
}

void Game::run()
{
	std::string s;
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point stop;
	const unsigned long* vals;
	unsigned long numberCount;
	while (true) {
		std::cout << "Was ist ist die Primfaktorzerlegung von " << task->genTask() << "?\n";
		start = std::chrono::high_resolution_clock::now(); //start chrono
		std::getline(std::cin, s);
		std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now(); //stop chrono
		vals = castInput(s,numberCount);
		if (task->checkFactorization(vals, numberCount)) { //check input
			std::cout << "Das ist korrekt. Gleich weiter!\n";
			currentPrimeProgress++;	//prime lvlup counter
			if (std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() < numberUpTime) { // amount of numbers lvlup/down
				currentNumbersProgress++;
			}
			else {
				currentNumbersProgress = 0;
				if (std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() > numberDownTime) {
					currentNumbersDownProgress++;
				}
			}
		}
		else {
			currentPrimeProgress = 0; //prime down progress
			currentPrimeDownProgress++; 
			currentNumbersDownProgress++; // Number down progress
			std::cout << "Das ist leider falsch.\nRichtig ist: ";
			for (unsigned long i = 0; i < task->primesLength; i++) { //print correct factorization
				std::cout << task->getPrimes()[i] << " ";
			}
			std::cout << "\nVersuch es doch gleich nochmal!\n";
		}
		calcNewLevels();
		delete[] vals;
	}
	delete[] vals;
}
