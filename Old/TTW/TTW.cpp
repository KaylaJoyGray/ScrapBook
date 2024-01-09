// TTW.cpp

#include "TTW_module.hpp"
#include <iostream>

int main (int argc, char **argv) {
    flecs::world ecs;

	//import module
	ecs.import<TTW::module>();

	return 0;
}
