	#ifndef GLOBAL_RNG_H
#define GLOBAL_RNG_H

#include <vector>
#include <string>

// you may have to write your own shuffle function to ensure that CALL_CNT is iterated
// correctly and ensures consistent results... further testing is needed
// https://en.cppreference.com/w/cpp/algorithm/random_shuffle
// 
// once other parts of the game are completed, it may make sense to have seperate RNGs for
// different parts of the game, such as world generation and world events
//
// you also need to implement an uncounted random function for things that the user can do
// which should not affect the overall RNG (for example, the player might choose to randomize
// their character on the creation screen, and this shouldn't affect terrain generation)

namespace global_RNG {
	// faiure to call this function before using the RNG will result in undefined behavior
	// therefore, should be called by both load game and new game functions
	void init_RNG(int seed, int init_CNT);
	
	// getters for RNG variables
	int SEED();
	unsigned long long int CALL_COUNT();
		
	//generate random integers in range
	int rand_int(int min, int max);
	int even_int(int min, int max);
	//generate random doubles in range
	double rand_double(double min, double max);
}

#endif
