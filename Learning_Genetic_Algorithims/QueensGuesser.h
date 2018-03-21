#pragma once

#include "Utilities.h"
#include <time.h>

using namespace std;


class Fitness
{
public:
	Fitness();
	Fitness(int totalQueens);
	~Fitness();

	bool operator>(const Fitness* fitnessB);

	int Get_TotalQueens() const
	{
		return _totalQueens;
	};

	string To_String();

private:
	int _totalQueens;
};

//Chromosomes are containers for the data we're trying to find
template <typename T>
class Chromosome
{

public:

	Chromosome();
	Chromosome(Fitness fitness, T* genes);
	~Chromosome();

	//Accessors
	virtual Fitness Get_Fitness() { return _fitness; };
	T* Get_Genes() { return &Genes; };

private:

	//variable
	Fitness _fitness;
	T Genes;

};

/*Generic Guesser
This is a base class that has general functionality for STL Containers. Specific behavior must be implement via child classes.
*/
template<typename T>
class QueensGuesser
{
public:
	QueensGuesser();
	~QueensGuesser();

	//Functions
	Chromosome<T> Get_Best(int targetLength, T* const genes, const Fitness* optimalFitness);

	//Acessors
	int Get_Generation() const { return generation; };//only let the user access this but not change it

protected:
	//Functions
	virtual void Display(Chromosome<T>* const guess);
	virtual Fitness Get_Fitness(T* const guess);
	virtual Chromosome<T> Mutate(T* const parent);
	virtual Chromosome<T> Generate_Parent(int const wordLength);
	void Init(int const targetLength, T* const genes);

	//Variables
	clock_t startTime;
	Chromosome<T> bestParent;
	T* geneSet;
	int _targetLength;
	Fitness bestFitness;
	int generation = 0;//how many generations have gone through
};

class Board
{

public:
	Board(vector<int>* genes, int size);
	~Board();

	string Print_Board();

	char** Get_Board() { return _board; };

private:
	char** _board;
	int _boardSize;
};
