// Learning_Genetic_Algorithims.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Utilities.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "QueensGuesser.h"

using namespace std;

/**/
template <class T, class U>
void DoGuess_Benchmark(int num_Guesses, T* genes, int size, U* guesser)
{
	clock_t currentTime;// init the time variable
	currentTime = clock();//now start the time variable so the countdown only considers the algorithm
	int average_Generations = 0;

	for (int i = 0; i < num_Guesses; ++i)
	{
		Fitness optimalFitness(0);

		cout << endl;
		guesser->Get_Best(size * 2, genes, &optimalFitness);
		average_Generations += guesser->Get_Generation();

		printf("\nGuess Number: %i/%i", i + 1, num_Guesses);
	}

	currentTime = clock() - currentTime;

	average_Generations /= num_Guesses;

	printf("\nAverage Generations: %i \nRuntime: %.3f seconds", average_Generations, (float)currentTime / CLOCKS_PER_SEC);

	cin.get();
	cin.get();
}


void EightQueens(int num_Guesses, int size)
{
	QueensGuesser<vector<int>> guesser;
	vector<int> genes;

	for (size_t i = 0; i < size; i++)//genes are numbers 0-7
		genes.push_back(i);

	DoGuess_Benchmark(num_Guesses, &genes, size, &guesser);
}

int main()
{
	bool isRunning = true;
	//input variables

	while (isRunning)
	{
		system("cls");

		string choice;

		cout << "[0] 8 Queens Problem\n" << endl;
		getline(cin, choice);

		int num_Guesses;
		cout << "Enter the number of times to run the algorithim: ";
		cin >> num_Guesses;

		if (choice == "0")
			EightQueens(num_Guesses, 8);
	}


	return 0;
}
