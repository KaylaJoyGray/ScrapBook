

#include "materials.hpp"
#include <cmath>

namespace materials {
 
	int apply_temperature(double delta, material mat, double temp)
	// applies temperature to a material, returns the amount of health lost
	{
		double resist = static_cast<double>(mat.heat_resistance);

		if (temp > mat.crit_temp) {
			return static_cast<int>(std::round(((temp - mat.crit_temp) / resist) * delta));
		} else {
			return 0;
		}
	}

	material aluminum = {
		100,
		100,
		true,
		1000,
		2000
	};

	material steel = {
		100,
		100,
		true,
		1000,
		2000
	};

	material ceramic_composite = {
		100,
		100,
		true,
		1000,
		2000
	};

}