#ifndef PHYSICS_COLLISION_HPP
#define PHYSICS_COLLISION_HPP

namespace scene::physics {
// physics START BRACE

		enum Collide_Resistance {
			resist_air,		// air resistance
			resist_thin,	// thin liquid
			resist_thick,	// thick liquid
			resist_solid,	// impassible
		};

		enum Collide_Size {
			size_small,
			size_full
		};

		struct Collision_Data {
			Collide_Resistance 	resistance;
			Collide_Size 		size;
		};

		void apply_resistance(double delta, Collide_Resistance r, double& speed);

// physics END BRACE
}

#endif