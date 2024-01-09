/*
 * TTW_module.cpp
 */

#include "TTW_module.hpp"

namespace TTW
//TTW START BRACE
{

module::module(flecs::world& world) {
	//Register module with world
	world.module<module>();

	//Register components
	world.component<Mark>;
	world.component<Pos>;
}

//TTW END BRACE
}

