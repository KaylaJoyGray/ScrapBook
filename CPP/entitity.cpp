#include <iostream>
#include <vector>
#include <string>

// health systems

// neurological
// skeletal
// circulatory
// respiratory
// digestive
// immune

class organ {
	private:
		std::string name;
		float health;
		float max_health;
		bool alive;
	public:
		organ(std::string set_name, float set_max) {
			name = set_name;
			max_health = set_max;
			alive = true;
		}
		void process(float healing_rate) {
			if (health <= 0) {
					alive = false;
			}
			
			if (alive) {
				if (health+(healing_rate)<=max_health) {
						health += healing_rate;
				}
			}
		}
		bool damage(float damage_factor) {
			bool killed = false;
			health -= damage_factor;
			if (health <= 0) {
				alive = false;
				killed = true;
			}
			
			return killed;
		}
		std::string name() {
			return name;
		}
		float health() {
			return health;
		}
};

class entity {
	private:
		int type;
		
		float age;
		
		float size;
		float max_size;
		
		int vision;
		int voice;
		int hearing;
		int smell;
		
		std::vector<organ> organs;
	
	public:
		entity(int t, float init_age, float init_size, float m_size) {
			type = t;
			age = init_age;
			size = init_size;
			max_size = m_size;
		}
		void add_organ(organ &new_organ) {
			organs.push_back(new_organ);
		}
		
		void damage_organ(std::string name, float damage_factor) {
			for (organ &current_organ : organs) {
				if (current_organ.name() == name) {
					current_organ.damage(damage_factor);
				}
			}
		}
		float calculate_neuro() {
			
		}
		float calculate_strenth() {
			
		}
		float calculate_blood() {
			
		}
		float calculate_air() {
			
		}
		float calculate_food() {
			
		}
		float calculate_heal() {
			
		}
		bool vision_check(int check) {
				bool passed = false;
				if (vision >= check) {
					passed = true;
				}
				return passed;
		}
		bool voice_check(int check) {
				bool passed = false;
				if (voice >= check) {
					passed = true;
				}
				return passed;
		}
		bool hearing_check(int check) {
				bool passed = false;
				if (hearing >= check) {
					passed = true;
				}
				return passed;
		}
		bool smell_check(int check) {
				bool passed = false;
				if (smell >= check) {
					passed = true;
				}
				return passed;
		}
		
		void idle() {
			
		}
};

int main(int argc, char **argv) {
	
		return 0;
}

