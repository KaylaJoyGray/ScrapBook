#ifndef MATERIALS_HPP
#define MATERIALS_HPP

#include "fixed_int.hpp"

namespace materials {

	struct material {
		uint16	init_health;
		
		uint16	heat_resistance;
		bool	meltable;			// if false, material will burn instead of melting
		double	crit_temp;			// temperature at which the material will start losing health		
		double	burn_temp;			// temperature at which the material will burn/melt
	};

	// applies temperature to a material, returns the amount of health lost
	int apply_temperature(double delta, material mat, double temp);

	// built-in material defintions
	extern material aluminum;
	extern material steel;
	extern material ceramic_composite;
}

#endif