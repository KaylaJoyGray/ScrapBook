#include <string>
#include <vector>
#include <iostream>

int charSum(std::vector<std::string> strings)
// returns the sum of all characters in a vector of strings
{
	if (strings.empty())
		return 0;

	return strings[0].length() + charSum(std::vector<std::string>(strings.begin()+1, strings.end()));
}

std::vector<int> toEven(std::vector<int> ints)
// returns a new vector with only even numbers from ints
{
	if (ints.empty())
		return {};

	std::vector<int> result;

	if (ints[0] % 2 == 0) {
		result.push_back(ints[0]);
	}

	auto next = toEven(std::vector<int>(ints.begin()+1, ints.end()));
	result.insert(result.end(), next.begin(), next.end());

	return result;
}

int triNum(int n)
// returns the nth triangular number
{
	if (n <= 0)
		return 0;

	return n + triNum(n-1);
}

int indX(std::string s)
// returns the first index found to contain an 'X'
// assumes that there is, in fact, an X
{
	if (s[0] == 'x' || s[0] == 'X')
		return 0;

	return 1 + indX(std::string(s.begin()+1, s.end()));
}

int shortestPaths(int r, int c)
// returns the number of shortest paths, given rows and columns
{
	if (r < 3 && c < 3)	// there 2 paths in a 2x2 square
		return 2;

	return 2 * (shortestPaths(r-1, c-1));
}

int pathsBook(int r, int c)
// checking to see if my solution is equivalent to solution in textbook (it's not!)
{
	if (r == 1 || c == 1)
		return 1;

	return pathsBook(r-1, c) + pathsBook(r, c-1);
}

int main(int arc, char** argv) {

	std::vector<std::string> strings = {"boy", "girl", "cat", "dog"};	// 13 chars

	std::cout << charSum(strings) << std::endl;

	std::vector<int> notEvens = {1, 3, 4, 2, 5, 8, 7, 6, 9}; // 4, 2, 8, 6

	for (auto i : toEven(notEvens)) {
		std::cout << i << ", ";
	}
	std::cout << std::endl;

	std::cout << triNum(7) << std::endl;	// 28

	std::cout << indX("yanex") << std::endl; // should print '4'

	std::cout << shortestPaths(3, 7) << std::endl; 
	std::cout << pathsBook(3, 7) << std::endl; 
}