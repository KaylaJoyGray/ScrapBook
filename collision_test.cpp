#include <unordered_set>
#include <iostream>

/* This is a test program to prove that a hash function is collision free 
 *
 * The following constraints are in place: x, y, z are unsigned int <= 250
 * 
 */

struct Position {
	int x, y, z;
};

std::size_t hash(Position p) {
	int result = 0;

	for (auto i : {p.x, p.y, p.z}) {
		result = (result * 1000) + i;
	}

	return result;
}

int main(int arc, char** argv) {
	std::unordered_set<std::size_t> hashes;

	for (int x = 0; x < 251; ++x) {
		for (int y = 0; y < 251; ++y) {
			for (int z = 0; z < 251; ++z) {
			
				if (hashes.emplace(hash({x, y, z})).second == false)
					std::cout << "Hash collision at " << hash({x, y, z}) << std::endl;
			}
		}
	}

	std::cout << "Reached end" << std::endl;
}