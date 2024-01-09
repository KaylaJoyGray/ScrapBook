
#include "physics_coordinates.hpp"
#include <functional>

using namespace scene::physics;

namespace scene::physics {
// game area START BRACE

	// external constants
	const uint8 CHUNK_SIZE = 250;
	const double TILE_SIZE = 40.0;

	bool Position::operator <(const Position& other) const
	// overloading the < operator allows the struct to be used as a multimap key
	{
		if (this->z != other.z)
			return (this->z < other.z);

		if (this->y != other.y)
			return (this->y < other.y);

		return (this->x < other.x);
	}

	bool Position::operator ==(const Position& other) const
	// overload == operator
	{
		return ((this->z == other.z) &&
				(this->y == other.y) &&
				(this->x == other.x));
	}

	std::size_t Position_Hash::operator()(const Position& p) const
	// hash function for Position
	{
		return std::hash<unsigned int>()(p.x) ^
			   std::hash<unsigned int>()(p.y) ^
			   std::hash<unsigned int>()(p.z);
	}

	bool pos_in_bounds(Position p)
	// performs bounds checking for a Position
	// returns true if Positon is in bounds
	{
		if ((p.x >= 0) && (p.x <= CHUNK_SIZE) &&
			(p.y >= 0) && (p.y <= CHUNK_SIZE) &&
			(p.z >= 0) && (p.z <= CHUNK_SIZE)) {
			return true;
		}

		return false;
	}

	bool off_in_bounds(Offset o)
	// performs bounds checking for an Offset
	// returns true if Offset is in bounds
	{
		if ((o.x >= 0.0) && (o.x <= CHUNK_SIZE) &&
			(o.y >= 0.0) && (o.y <= CHUNK_SIZE) &&
			(o.z >= 0.0) && (o.z <= CHUNK_SIZE)) {
			return true;
		}

		return false;
	}

// game area END BRACE
}