/*
 * main.cpp
 * 
 */
 
#include "body_parts.h"
#include <iostream>

organ_type string_to_organ_type(std::string input) {
	//coverts a string to an organ type
	organ_type result;
	
	if (input == "soft") {
		result = type_soft;
	} else if (input == "bony") {
		result = type_bony;
	} else if (input == "muscle") {
		result = type_muscle;
	} else if (input == "major digits") {
		result = type_major;
	} else if (input == "minor digits") {
		result = type_minor;
	} else if (input == "combo digits") {
		result = type_combo;
	} else if (input == "booster") {
		result = type_booster;
	} else {
		std::cerr<<"Warning! Could not convert string to organ type: "<<input<<"\n";
		result = type_none;
	}
	
	return result;
}

organ_trait string_to_organ_trait(std::string input)
//convert a string to an organ trait
{
	organ_trait result;
	
	if (input == "cognition") {
		result = trait_cognitive;
	} else if (input == "nervous") {
		result = trait_nervous;
	} else if (input == "circulatory") {
		result = trait_circulatory;
	} else if (input == "respiratory") {
		result = trait_respiratory;
	} else if (input == "digestive") {
		result = trait_digestive;
	} else if (input == "filtration") {
		result = trait_filtration;
	} else if (input == "immune") {
		result = trait_immune;
	} else if (input == "stomach") {
		result = trait_stomach;
	} else if (input == "vision"){
		result = trait_vision;
	} else if (input == "hearing") {
		result = trait_hearing;
	} else if (input == "voice") {
		result = trait_voice;
	} else if (input == "taste") {
		result = trait_taste;
	} else if (input == "smell") {
		result = trait_smell;
	} else {
		std::cerr<<"Warning! Could not convert string to organ trait:<<"<<input<<"\n";
		result = trait_none;
	}
	
	return result;
}

int base_part::get_id() {
	return id;
}

std::string base_part::get_name() {
	return name;
}

void base_part::sever() {
	if (severable) {
		attached = false;
	}
}

bool base_part::is_attached() {
	return attached;
}

organ::organ(
			int set_id,
			std::string set_name,
			float set_mass,
			enum organ_type set_type,
			enum organ_trait set_system1,
			int set_system1_weight,
			enum organ_trait set_system2,
			int set_system2_weight
			)
		{
			id = set_id;
			
			type = set_type;
			
			name = set_name;
			
			system1 = set_system1;
			system1_weight = set_system1_weight;
			
			system2 = set_system2;
			system2_weight = set_system2_weight;
						
			mass = set_mass;
			max_health = set_mass*100;
			
			health = max_health;
			alive = true;
}
		
		
bool organ::add_system(enum organ_trait new_system, int new_weight) {
	bool set = false;
	if (system1 == trait_none) {
		system1 = new_system;
		system1_weight = new_weight;
		set = true;
	} else if (system2 == trait_none) {
		system2 = new_system;
		system2_weight = new_weight;	
		set = true;
	}
	return set;
}
void organ::idle(float healing_rate) {
	if (health <= 0) {
			alive = false;
	}
	
	if (alive) {
		if (health+(healing_rate)<=max_health) {
				health += healing_rate;
		}
	}
}

bool organ::damage(float damage_factor) {
	bool killed = false;
	health -= damage_factor;
	if (health <= 0) {
		alive = false;
		killed = true;
	}
	
	return killed;
}


enum organ_type organ::get_type() {
	return type;
}
float organ::get_health() {
	return health;
}
bool organ::is_alive() {
	return alive;
}
float organ::get_mass() {
	return mass;
}
int organ::get_system1() {
	return system1;
}
int organ::get_system1_weight() {
	return system1_weight;
}
int organ::get_system2() {
	return system2;
}
int organ::get_system2_weight() {
	return system2_weight;
}


part::part(int set_id, std::vector<int> &set_depends, bool set_sever, std::vector<int> &set_organs) {
		id = set_id;
		child_of = set_depends;
		
		severable = set_sever;
		attached = true;
		
		organ_ids = set_organs;
}

std::vector<int> part::get_ids() {
	return organ_ids;
}
std::vector<int> part::get_parents() {
	return child_of;
}
