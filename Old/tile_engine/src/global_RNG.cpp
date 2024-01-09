/*
 * global_RNG.cpp
 *
 */

#include "global_RNG.hpp"
#include <cmath>
#include <memory>
#include <random>

namespace global_RNG {

	namespace {
		int GLOBAL_SEED;
		std::unique_ptr<std::mt19937> RNG;
		// CALL_CNT is incremented every time a random
		unsigned long long int CALL_CNT;
	}

	/*****************************************************************
	 *  functions to access the RNG variables
	 ****************************************************************/

	int SEED()
	// returns the current random seed
	{
		return GLOBAL_SEED;
	}

	unsigned long long int CALL_COUNT()
	// returns the number of times the RNG has been called
	{
		return CALL_CNT;
	}

	/*****************************************************************
	 *  functions to access the RNG variables
	 ****************************************************************/

	void init_RNG(int seed, int init_CNT)
	// faiure to call this function before using the RNG will result in undefined behavior
	// therefore, should be called by both load game and new game functions
	{
		GLOBAL_SEED = seed;
		CALL_CNT = init_CNT;
		RNG.reset(new std::mt19937(GLOBAL_SEED));

		for (int cnt = 0; cnt < init_CNT; cnt++) {
			(*RNG)();
		}
	}

	int rand_int(int min, int max) {
		if (max < min) {
			// segmentation fault will result if min>max
			int new_min = max;
			max = min;
			min = new_min;
		}

		std::uniform_int_distribution<int> dist(min,max);
		int result = dist(*RNG);

		CALL_CNT++;
		return result;
	}

	int even_int(int min, int max) {
		int result = rand_int(min, max);
		result = round(result/2)*2;

		return result;
	}

	double rand_double(double min, double max) {
		if (max < min) {
			// segmentation fault will result if min>max
			double new_min = max;
			max = min;
			min = new_min;
		}

		std::uniform_real_distribution<double> dist(min,max);
		double result = dist(*RNG);

		CALL_CNT++;
		return result;
	}

}
