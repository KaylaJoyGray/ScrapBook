// sat cleanup:
// clean up std::endl spam
// current objective:
// dynamically generate an entire body

#include "body_parts.h"
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <fstream>

void trim_string(std::string &input)
// remove the whitespace from the start and end of a string
{
	if (input.length() > 0) {
		std::string white_space = " \n\r\t\f\v";
		
		std::string::size_type start = input.find_first_not_of(white_space);
		std::string::size_type end = input.find_last_not_of(white_space);
		
		input = input.substr(start,end+1);
	}
}

class entity {
	protected:
		std::string name;
		std::string species_name;
		
		std::string file_path;
		
		std::vector<part> part_list;
				
		/*std::map<int, int> system_status{
				{system_cognitive, 0},
				{system_nervous, 0},
				{system_circulatory, 0},
				{system_respiratory, 0},
				{system_filtration, 0},
				{system_immune, 0},
		};
		
		std::map<int, int> sense_status {
				{sense_vision, 0},
				{sense_hearing, 0},
				{sense_voice, 0},
				{sense_taste, 0},
				{sense_smell, 0},
		};*/
		
		float max_blood_level;
		float max_fat_level;
		float max_food_level;
		
		float low_temp;
		float high_temp;
		float ideal_temp;
		
		float hunger_rate;
		
		// vitals
		float blood_level;
		float food_level;
		float fat_level;
		float temp;
		
		bool endotherm;
		int blood_type;

		// variables for organ file loading
		std::string set_name;
		enum organ_type set_type;
		enum organ_trait set_system1;
		int set_system1_weight;
		enum organ_trait set_system2;
		int set_system2_weight;
		float set_mass;
	
	public:
		entity(
			std::string set_name,
			std::string set_species,
			std::string set_file_path,
			float set_max_blood_level,
			float set_max_fat_level,
			float set_max_food_level,
			float set_low,
			float set_ideal,
			float set_high,
			float set_blood_level,
			float set_fat_level,
			float set_food_level,
			float set_temp,
			float set_hunger_rate,
			bool set_therm,
			int set_blood_type)
		{
			name = set_name;
			species_name = set_species;
			file_path = set_file_path;
			
			max_blood_level = set_max_blood_level;
			max_fat_level = set_max_fat_level;
			max_food_level = set_max_food_level;
		
			low_temp = set_low;
			high_temp = set_high;
			ideal_temp = set_ideal;
		
			hunger_rate = set_hunger_rate;
		
			blood_level = set_blood_level;
			food_level = set_food_level;
			fat_level = set_fat_level;
			temp = set_temp;
		
			endotherm = set_therm;
			blood_type = set_blood_type;
		}
		
		void load_body_parts() {
			reset_file_load_vars();
			
			std::string organ_path = file_path+"organs";
			std::string parts_path = file_path+"parts";
			
			std::ifstream reader;
			std::string line;
			std::string::size_type string_index;

			
			//substrings for string parsing
			std::string fr_flag;
			std::string first_char;
			
			reader.open(organ_path);
			
			if (!reader) {
				std::cerr<<"Error! could not open organ file: "<<organ_path<<"\n";
			}
			
			std::vector<organ> loaded_organs;
			
			//for ptype (push organs of type command)
			organ_type push_type;
			std::vector<std::pair<float,std::string>> push_values; 
			
			bool push_search=false;
						
			int id_ctr = 0;
			while(std::getline(reader, line)) {	
				trim_string(line);
				
				if (line.length() > 2) {
					first_char = line.substr(0,1);
					fr_flag = line.substr(0,3);
				
					if (not push_search and first_char == ":") {											
						if (check_assn(line)) {
							string_index = line.find("=");

							
							if (fr_flag == ":na") {
									set_name = line.substr(string_index+1);
									trim_string(set_name);
							} else
							
							if (fr_flag == ":ty") {
									std::string t_input = line.substr(string_index+1);
									trim_string(t_input);
									set_type = string_to_organ_type(t_input);
							} else
							
							if (fr_flag == ":ma") {
									std::string m_input = line.substr(string_index+1);
									trim_string(m_input);
									try {
										set_mass = std::stof(m_input);
									} catch (const std::invalid_argument& invalid) {
										std::cerr<<"Warning! Error parsing organ file: expected mass to be of type float\n";
										set_mass = 0.0;
									}
							} else
							
							if (fr_flag == ":ad") {
									std::string t_input = line.substr(string_index+1);
									std::string::size_type comma = t_input.find(",");
									
									if (!string_index_valid(comma, line)) {
										std::cerr<<"Warning! Error parsing organ file: expected 2 arguments\n";
									}
									
									std::string trait_name = t_input.substr(0, comma);
									trim_string(trait_name);
									
									organ_trait add_trait = string_to_organ_trait(trait_name);
									
									std::string trait_weight_s = t_input.substr(comma+1);
									trim_string(trait_weight_s);
																
									int trait_weight = -1;
									try {
										trait_weight = std::stoi(trait_weight_s);
									} catch (const std::invalid_argument& invalid) {
										std::cerr<<"Warning! Error parsing organ file: expected second argument to be of type int\n";
									}
																
									if (set_system1 == trait_none) {
										set_system1 = add_trait;
										set_system1_weight = trait_weight;
									} else if (set_system2 == trait_none) {
										set_system2 = add_trait;
										set_system2_weight = trait_weight;
									} else {
										std::cerr<<"Warning! Error parsing organ file: organ cannot have more than 2 traits\n";
									}
							} else
							
							if (fr_flag == ":pt") {
								std::string t_string = line.substr(string_index+1);
								trim_string(t_string);
								push_type = string_to_organ_type(t_string);
								
								push_search = true;
								continue;
							}
						}
					}
					
					if (fr_flag == ":en") {
						if (not push_search) {
							if (set_name == " " or set_type == type_none or set_mass == 0.0) {
								std::cerr<<"Warning! Error parsing organ file: need valid name, type, and mass before ':end'\n";
							} else {
								organ new_organ(
									id_ctr,
									set_name,
									set_mass,
									set_type,
									set_system1,
									set_system1_weight,
									set_system2,
									set_system2_weight);
									
								loaded_organs.push_back(new_organ);
								id_ctr++;
							}
								
							reset_file_load_vars();
						} else {
							if (push_type == type_none or push_values.empty()) {
								std::cerr<<"Warning! Error parsing organ file: need valid name, type, and mass before ':end'\n";
							} else {
								for (std::pair<float, std::string> next_pair : push_values) {
									organ new_organ(
									id_ctr,
									std::get<1>(next_pair),
									std::get<0>(next_pair),
									push_type
									);
								
									id_ctr++;
								}	
							}
							
							push_type = type_none;
							push_values.clear();
							
							push_search = false;
						}
					} else {
						std::string::size_type comma = line.find(",");
						
						if (!string_index_valid(comma, line)) {
							std::cerr<<"Warning! Error parsing organ file: expected 2 arguments\n";
						}
						
						std::string weight_string = line.substr(0, comma);
						trim_string(weight_string);
						
						std::cout<<weight_string<<"\n";
						
						int new_mass;
						try {
							new_mass = std::stof(weight_string);
						} catch (const std::invalid_argument& invalid) {
							std::cerr<<"Warning! Error parsing organ file: expected mass to be of type float\n";
							new_mass = 0.0;
						}
						
						std::string new_name = line.substr(comma+1);
						trim_string(new_name);
						
						std::cout<<new_name<<"\n";
						
						std::pair<float, std::string> new_pair = std::make_pair(new_mass, new_name);
						
						push_values.push_back(new_pair);
					}
			}
			std::cout<<loaded_organs.size();
			}
		}
		
		bool check_assn(std::string line)
		// check to see if assignment operation for a line is properly formed
		{	
			bool valid = true;
			std::string::size_type string_index = line.find("=");
			if (not string_index_valid(string_index, line)) {
				valid = false;
			}
			
			return valid;
		}
		
		bool string_index_valid(std::string::size_type string_index, std::string index_of)
		//checks that a string index is not invalid or at the end of a string
		{
			bool result = true;
			
			if (string_index == std::string::npos or string_index == index_of.size()) {
				result = false;				
			}
			
			return result;
		}
		
		void reset_file_load_vars() {
			std::string set_name = " ";
			set_type = type_none;
			set_system1 = trait_none;
			set_system1_weight = -1;
			set_system2 = trait_none;
			set_system2_weight = -1;
			set_mass = 0.0;	
		}
};

enum species_type {
	type_custom = -1,
	type_human
};

entity generate_template(enum species_type type) {
	std::string set_name;
	std::string set_species;
	std::string set_file_path;
	float set_max_blood_level;
	float set_max_fat_level;
	float set_max_food_level;
	float set_low;
	float set_ideal;
	float set_high;
	float set_blood_level;
	float set_fat_level;
	float set_food_level;
	float set_temp;
	float set_hunger_rate;
	bool set_therm;
	int set_blood_type;
	
	switch(type) {
		default:
			set_name = "human";
			set_species = "human";
			set_file_path = "./data/entities/human/";
			set_max_blood_level = 5.0;
			set_max_fat_level = 200.0;
			set_max_food_level = 10.0;
			set_low = 21.0;
			set_ideal = 37.0;
			set_high = 43.0;
			set_therm = true;
			set_blood_type = 0;
			set_blood_level = 5.0;
			set_food_level = 10.0;
			set_hunger_rate = 1.0;
			set_fat_level = 12.0;
			set_therm = true;
		break;
	}
	
	entity result(
			set_name,
			set_species,
			set_file_path,
			set_max_blood_level,
			set_max_fat_level,
			set_max_food_level,
			set_low,
			set_ideal,
			set_high,
			set_blood_level,
			set_fat_level,
			set_food_level,
			set_temp,
			set_hunger_rate,
			set_therm,
			set_blood_type
	);
	
	return result;
}

int main(int argc, char **argv) {
		entity test = generate_template(type_human);
		test.load_body_parts();
	
		return 0;
}

