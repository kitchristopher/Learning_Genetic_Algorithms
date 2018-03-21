#include "QueensGuesser.h"
#include <cmath>
#include <random>
#include <ctime>
#include <string>
#include <set>

#pragma region  Fitness_Region

Fitness::Fitness()
{
}

Fitness::Fitness(int totalQueens)
{
	_totalQueens = totalQueens;
}

Fitness::~Fitness()
{
}

//To avoid the other equilency operators, various logical tricks are used
bool Fitness::operator>(const Fitness * fitnessB)
{
	return _totalQueens < fitnessB->Get_TotalQueens();
}

string Fitness::To_String()
{
	return "Total Unsafe Queens: " + to_string(_totalQueens);
}
#pragma endregion

template<typename T>
Chromosome<T>::Chromosome() {}

template<typename T>
Chromosome<T>::Chromosome(Fitness const fitness, T* const genes)
{
	_fitness = fitness;
	Genes = *genes;
}

template<typename T>
Chromosome<T>::~Chromosome() {}

template<typename T>
QueensGuesser<T>::QueensGuesser() {}

template<typename T>
QueensGuesser<T>::~QueensGuesser() {}


template<typename T>
void QueensGuesser<T>::Init(int const targetLength, T* const genes)
{
	startTime = clock();
	generation = 0;
	geneSet = genes;
	_targetLength = targetLength;
	bestParent = Generate_Parent(_targetLength);
	bestFitness = bestParent.Get_Fitness();

	Display(&bestParent);//show the inital starting gene
}

/*
Given a set of genes, the algorithim will return an optimal solution.

@param: "Goal", the target to find
@param: "Genes", the data that can be used to find the target
@param: "optimalFitness", the value the algorithim will stop at
@return: the chromosome of the child
*/
template<typename T>
Chromosome<T> QueensGuesser<T>::Get_Best(int const targetLength, T * const genes, const Fitness* optimalFitness)
{
	Init(targetLength, genes);

	auto derefOptimalFitness = *optimalFitness;

	if (!(derefOptimalFitness > &bestParent.Get_Fitness()))
		return bestParent;

	while (true)
	{
		Chromosome<T> child = Mutate(bestParent.Get_Genes());
		++generation;

		if (bestParent.Get_Fitness() > &child.Get_Fitness())//discard smaller children
			continue;
		if (!(child.Get_Fitness() > &bestParent.Get_Fitness()))//if the child is equal, use it
		{
			bestParent = child;
			continue;
		}

		Display(&child);

		if (!(derefOptimalFitness > &child.Get_Fitness()))
			return child;

		bestParent = child;
	}
}



template<typename T>
void QueensGuesser<T>::Display(Chromosome<T>* const guess)
{
	clock_t currentTime = clock() - startTime;
	float deltaTime = (float)currentTime / CLOCKS_PER_SEC;

	Board board(guess->Get_Genes(), _targetLength / 2);

	cout << board.Print_Board() << endl;

	string result = "Genes: [ ";

	for (auto it = guess->Get_Genes()->begin(); it != guess->Get_Genes()->end(); ++it)
		result += to_string(*it) + ", ";

	result += "]";

	printf("%s Seconds: %f %s  Generation: %i \n", result.c_str(), deltaTime, guess->Get_Fitness().To_String().c_str(), generation);
}

template<typename T>
//Returns a count of the adjacent numbers in ascending order
Fitness QueensGuesser<T>::Get_Fitness(T * const guess)
{
	int size = _targetLength / 2;

	Board board(guess, size);

	//sets only have unique elements, thus by inserting the position of the queen, we can count how many times the queens are on an attacking path 
	//since they wont be added if they are
	set<int> rowsWithQueens;
	set<int> columnsWithQueens;
	set<int> northeastDiagonalWithQueens;
	set<int> southeastDiagonalWithQueens;

	for (size_t row = 0; row < size; row++)
	{
		for (size_t column = 0; column < size; column++)
		{
			if (board.Get_Board()[column][row] == 'Q')
			{
				rowsWithQueens.insert(row);
				columnsWithQueens.insert(column);
				northeastDiagonalWithQueens.insert(row + column);
				southeastDiagonalWithQueens.insert(size - 1 - row + column);
			}
		}
	}


	int totalQueens = size - rowsWithQueens.size() +			\
		size - columnsWithQueens.size() +						\
		size - northeastDiagonalWithQueens.size() +				\
		size - southeastDiagonalWithQueens.size();				

	return Fitness(totalQueens);
}

//MUTATE
/*
Creates a new randomly mutated child  from the given parent. The parent is not changed.

@param: "parentGenes", the original input.
@return: the mutated child from the parent.
*/
template<typename T>
Chromosome<T> QueensGuesser<T>::Mutate(T* const parentGenes)
{
	random_device seed;
	mt19937 rndGenerator(seed());
	uniform_int_distribution<int> distRange(0, parentGenes->size() - 1);//prepare the random distribution from the parent's indices

	int index = distRange(rndGenerator);//choose a random index 
	T childGenes = *parentGenes;//copy the child from the parent so we don't change the parent
	T chosenGenes = Utilities::Random::Sample(geneSet, 2);//create a new geneset from two random sampled genes

	auto alternate = chosenGenes[0];
	auto newGene = chosenGenes[1];//choose these two chars but create an alternative in case the char chosen was the same as before

	childGenes[index] = (newGene == childGenes[index]) ? alternate : newGene;//replace the corresponding index with the randomly chosen char

	T* genes = &childGenes;
	Fitness fitness = Get_Fitness(genes);

	return Chromosome<T>(fitness, genes);//the child genes are now mutated from the original parent
}


/*
Creates the first generation to the required size.

@params: the length the parent should be
@return: the chromosome of the parent
*/
template<typename T>
Chromosome<T> QueensGuesser<T>::Generate_Parent(int const wordLength)
{
	T genes;

	while (genes.size() < wordLength)
	{
		int sampleSize = fmin(wordLength - genes.size(), geneSet->size());

		T newGenes = Utilities::Random::Sample(geneSet, sampleSize);
		genes.insert(genes.end(), newGenes.begin(), newGenes.end());
	}

	Fitness fitness = Get_Fitness(&genes);

	return Chromosome<T>(fitness, &genes);
}


template class QueensGuesser<vector<int>>;
template class Chromosome<vector<int>>;


Board::Board(vector<int>* genes, int size)
{
	_boardSize = size;
	char** board = new char*[size];

	//A 2D array is an array of pointers, where each pointer points to value based arrays of the actual objects

	for (size_t i = 0; i < size; i++)//create an array dynamically
		board[i] = new char[size];

	for (size_t column = 0; column < size; column++)
	{
		for (size_t row = 0; row < size; row++)
		{
			board[column][row] = '.';
		}
	}

	for (size_t i = 0; i < genes->size(); i += 2)
	{
		int row = genes->at(i);
		int column = genes->at(i + 1);
		board[column][row] = 'Q';
	}

	_board = board;
}

Board::~Board()
{
	delete _board;
}

string Board::Print_Board()
{
	string result = "";

	for (size_t y = 0; y < _boardSize; y++)
	{
		for (size_t x = 0; x < _boardSize; x++)
		{
			result += _board[x][y];

			if (x == _boardSize - 1)
				result += "\n";
		}
	}

	return result;
}
