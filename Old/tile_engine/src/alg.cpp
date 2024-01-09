/*
 * alg.cpp
 * 
 * A collection of commonly used, shared functions
 * 
 */

#include "alg.hpp"

int alg::to_int(double d)
// rounds a double to the nearest int
{
	int result;
	
	if (d>0) {
		result = (d+0.5);
	} else {
		result = (d-0.5);
	}
			
	return result;
}
