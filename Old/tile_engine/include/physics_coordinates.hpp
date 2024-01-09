#ifndef PHYSICS_COORDINATES_HPP
#define PHYSICS_COORDINATES_HPP

#include "fixed_int.hpp"

namespace scene::physics {

		extern const uint8 CHUNK_SIZE;	//equivalent to max value of Position x, y, and z
		extern const double TILE_SIZE;	//equivalent to max value of Offset x, y, and z

		struct Position {
			uint8 x, y, z;
			bool operator  <(const Position& other) const;
			bool operator ==(const Position& other) const;
		};

		struct Position_Hash {
			std::size_t operator()(const Position& p) const;
		};

		bool pos_in_bounds(Position p);

		struct Offset {
			double x, y, z;
		};

		bool off_in_bounds(Offset o);

		enum Dir_3d {
					dir_n,  dir_ne,  dir_e,  dir_se,  dir_s,  dir_sw,  dir_w,  dir_nw,
			dir_u,  dir_un, dir_une, dir_ue, dir_use, dir_us, dir_usw, dir_uw, dir_unw,
			dir_d,  dir_dn, dir_dne, dir_de, dir_dse, dir_ds, dir_dsw, dir_dw, dir_dnw
		};

		enum Dir_3d_card {
			//only cardinal directions
			dirc_n, dirc_s, dirc_e, dirc_w, dirc_u, dirc_d
		};


}

#endif