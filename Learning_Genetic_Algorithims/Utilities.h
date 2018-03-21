#pragma once
#include <random>
#include <algorithm>
#include <iostream>

namespace Utilities
{

	namespace Random
	{
	
		//Sample
		/*
		Returns a sample of elements from a larger population set, without replacement. Leaves the original population unchanged.

		@param: "population_Input" type T, the larger set to take the sample from.
		@param: "k_Length" type int, the size of the returned sample.
		@return: type T, set of k_length samples from the given population_Input;
		*/
		template<typename T>
		T Sample(T* const population_Input, unsigned int k_Length)
		{
			/*
			0. Check if sample is within range. K must be < than population.
			1. Loop while the sample is smaller than K.
			2. Randomly select an element from the population.
			3. Remove the element from the population.
			4. Add it to the sample set.
			5. Repeat until the [1] is satisfied and return the sample set.
			*/

			T sampleSet;
			T inputCopy(*population_Input);//make a copy so we don't ruin the population input

			//EXCEPTION: OUF OF RANGE 
			if (k_Length > population_Input->size())
			{
				cout << "Exception: The requested sample size is greater than the population set." << endl;
				throw out_of_range("");
			}

			random_device seed;//create a true random number for the seed
			mt19937 rndGenerator(seed()); // generate the prnd generator

			while (sampleSet.size() < k_Length)
			{
				uniform_int_distribution<int> distRange(0, inputCopy.size() - 1);//the range for the generator to use

				int index = distRange(rndGenerator);
				auto* newElement = &inputCopy[index];//choose a random element from the input population

				sampleSet.push_back(*newElement);
				inputCopy.erase(inputCopy.begin() + index);//delete the element from the copy so it cannot be reselected
			}

			return sampleSet;
		}


	}

}