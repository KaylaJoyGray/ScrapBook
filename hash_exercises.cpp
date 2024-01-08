#include <vector>
#include <unordered_set>
#include <string>
#include <iostream>

std::vector<int> intersection(std::vector<int>& vec1, std::vector<int>& vec2)
// returns a vector with the values in common between vec1 and vec2
{
	std::unordered_set<int> lu;
	std::vector<int> result;

	for (auto i : vec1) {
	
		lu.emplace(i);
	}

	for (auto i : vec2) {
	
		if (lu.contains(i))
			result.push_back(i);
	}

	return result;
}

std::string getDuplicate(std::vector<std::string>& vec)
// returns the first duplicate string found
{
	std::unordered_set<std::string> lu;

	for (auto s : vec) {
		
		if (lu.contains(s))
			return s; 

		lu.emplace(s);
	}

	return " ";
}

char missingLetter(std::string in)
// returns the first letter of the alphabet found to be missing from string
{
	std::vector<char> alpha = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
	'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

	std::unordered_set<char> lu;

	for (auto c : in) {

		lu.emplace(c);
	}

	for (auto c : alpha) {
	
		if (!lu.contains(c))
			return c;
	}

	return ' ';
}

char firstUnique(std::string in)
// returns the first unique character found in the string
{
	std::unordered_set<char> lu;
	std::unordered_set<char> dupes;	//duplicates

	for (auto i = in.begin(); i != in.end(); ++i) {
	
		if (lu.emplace(*i).second == false)
			dupes.emplace(*i);
	}

	for (auto c : in) {

		if (!dupes.contains(c))
			return c;
	}

	return ' ';
}

int main(int argc, char** arv) {

	std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	std::vector<int> vec2 = {3, 5, 7};

	auto c = intersection(vec1, vec2);

	std::cout << "{";
	for (auto i : c) {
		std::cout << i << ", "; 
	}
	std::cout << "}" << std::endl;

	std::vector<std::string> svec = {"cat", "mouse", "dog", "dog", "duck", "fish"};

	std::cout << getDuplicate(svec) << std::endl;

	std::string nof = "the quick brown box jumps over a lazy dog";
	std::cout << missingLetter(nof) << std::endl;

	std::cout << firstUnique("minimum") << std::endl;
}