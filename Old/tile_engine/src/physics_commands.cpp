/*
 * physics_commands.cpp
 *
 * Copyright 2023 Kayla Gray
 *
 */

#include "physics.hpp"
#include <iostream>

using namespace scene::physics;

namespace scene::physics {
// physics START BRACE

	void Physics_Commands::add(Nudge_Command C)
	// add a Nudge_Command to the queue and increment the counter
	{
		nudge_commands.push(C);
		++nudge_ctr;
	}

// physics END BRACE
}
