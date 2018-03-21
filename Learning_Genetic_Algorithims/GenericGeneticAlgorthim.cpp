#include "GenericGeneticAlgorthim.h"
#include <cmath>
#include <random>


GenericGeneticAlgorthim::GenericGeneticAlgorthim()
{
}


GenericGeneticAlgorthim::~GenericGeneticAlgorthim()
{
}

string GenericGeneticAlgorthim::Generate_Parent(int wordLength)
{
	string genes = "";

	while (genes.size() < wordLength)
	{
		int sampleSize = fmin(wordLength - genes.size(), geneSet.size());
		//genes.append(rand())
	}

	return string();
}
