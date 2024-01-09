
#include "physics_collision.hpp"

namespace scene::physics {
// physics START BRACE

	void apply_resistance(double delta, Collide_Resistance r, double& speed)
	// modifies speed based on the resistance type
	{
		switch(r) {
			case resist_solid:
				speed = 0.0;
				break;
			case resist_thick:
				speed -= (0.1 * delta);
				break;
			case resist_thin:
				speed -= (0.01 * delta);
				break;
			case resist_air:
				speed -= (0.001 * delta);
				break;
		}
	}

// physics END BRACE
}