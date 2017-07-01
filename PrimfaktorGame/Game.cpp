#include "Game.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <chrono>

Game::~Game()
{
	delete dif;
	delete task;
}

Game::Game(int PrimeUpDifficulty, double speedLimit, int NumberUpDifficulty) : lvlUpPrimes(PrimeUpDifficulty), numberUpTime(speedLimit), lvlUpNumbs(NumberUpDifficulty)
{
}

void Game::init()
{
	std::cout << "Hallo!\nHier darfst du Zahlen in ihre Primfaktoren zerlegen.\nGib die Primzahlen einfach mit Leerzeichen getrennt ein.\nBitte gib den Dateinamen des Spielstandes an (Falls du keinen hast einfach direkt Enter benutzen) : ";
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
	std::string buf;
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point stop;
	long* vals;
	while (true) {
		std::cout << "Was ist ist die Primfaktorzerlegung von " << task->genTask() << "?\n";
		start = std::chrono::high_resolution_clock::now(); //start chrono
		std::getline(std::cin, s);
		std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now(); //stop chrono
		std::stringstream iss(s); //split string at " "
		std::vector<std::string> numbers;
		while (iss >> buf) {
			numbers.push_back(buf);
		}
		vals = new long[numbers.size()];	//convert string
		for (long i = 0; i < numbers.size(); i++) {
			vals[i] = std::atol(numbers.at(i).c_str());
		}

		if (task->checkFactorization(vals, numbers.size())) { //check input
			std::cout << "Das ist korrekt. Gleich weiter!\n";
			currentPrimeProgress++;	//prime lvlup
			if (currentPrimeProgress == lvlUpPrimes) {
				dif->increaseMaxPrime();
				currentPrimeProgress = 0;
			}
			if (std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() < numberUpTime) { // amount of numbers lvlup
				currentNumbersProgress++;
				if (currentNumbersProgress == lvlUpNumbs) {
					dif->setMaxNumbers(dif->getMaxNumbers() + 1);
					currentNumbersProgress = 0;
				}
			}
			else {
				currentNumbersProgress = 0;
			}
		}
		else {
			currentPrimeProgress = 0;
			std::cout << "Das ist leider falsch.\nRichtig ist: ";
			for (long i = 0; i < task->primesLength; i++) { //print correct factorization
				std::cout << task->getPrimes()[i] << " ";
			}
			std::cout << "\nVersuch es doch gleich nochmal!\n";
		}
		delete[] vals;
	}
	delete[] vals;
}
