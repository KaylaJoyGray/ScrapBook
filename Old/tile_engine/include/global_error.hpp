#ifndef GLOBAL_ERROR_H
#define GLOBAL_ERROR_H

#include <string>

namespace global_error {
	// logs an error to the error file ("./log.txt")
	void log_error(std::string message);
	// kills the program with an error message
	void fatal_error(std::string message);
}

#endif
