#pragma once

#include <string>
#include "Utilities.h"

using namespace std;
using namespace Utilities;

class GenericGeneticAlgorthim
{
public:
	GenericGeneticAlgorthim();
	~GenericGeneticAlgorthim();

	int Get_Fitness();
	string Generate_Parent(int wordLength);
	
	string geneSet  = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!.";
	string target = "a";
};

