/*
 * global_error.cpp
 *
 * Error reporting functions
 *
 */

#include "global_error.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

static void error_window(std::string title, std::string message)
// displays an error window && sends to cerr (in case all else fails)
{
	std::cerr<<message<<std::endl;
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), NULL);
}

void global_error::log_error(std::string message)
// logs an error to the error file ("./log.txt")
{
	std::cout << message << std::endl;

	std::ofstream log_file("./log.txt", std::ios::app);

	if (log_file.is_open()) {
		log_file<<message<<std::endl;
	} else {
		error_window("Error", "Cannot access error log! Check write permissions\n"+message);
	}
}

void global_error::fatal_error(std::string message)
// displays the error & kills the program
{
	log_error(message);
	error_window("Fatal Error", message);
	exit(EXIT_FAILURE);
}
