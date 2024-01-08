#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>

int add_until_100(std::vector<int> arr)
// adds every number, skipping if the number will take the result higher than 100
// this should be O(n)
{
	std::cout << "called add_until_100" << std::endl;
	if (arr.empty())
		return 0;

	int result = add_until_100(std::vector<int>(arr.begin()+1, arr.end()));

	if (arr[0] + result > 100)
		return result;

	return arr[0] + result;
}

int golomb(int n, std::unordered_map<int, int>& memo)
// memoized version of "golomb" sequence from textbook
// pass memo by reference; if there is copying this becomes incredibly slow
{
	if (n == 1)
		return 1;

	if (!memo.contains(n))
		memo[n] = 1 + golomb(n - golomb(golomb(n - 1, memo), memo), memo);

	return memo[n];
}

struct int2 {
	int first, second;

	bool operator==(const int2& other) const {
		return (this->first == other.first && this->second == other.second);
	}
};

struct hash {
	std::size_t operator()(const int2 a) const {
		std::size_t h = 0;

		h ^= std::hash<int>{}(a.first) + 0x9e3779b9 + (h << 6) + (h >> 2); 
		h ^= std::hash<int>{}(a.second) + 0x9e3779b9 + (h << 6) + (h >> 2); 
		
		return h;
	}
};

int unique_paths(int r, int c, std::unordered_map<int2, int, hash>& memo)
// memoized version of unique_paths from textbook
{
	if (r == 1 || c == 1)
		return 1;

	int2 key {r, c};

	if (!memo.contains({r, c}))
		memo[key] = unique_paths(r - 1, c, memo) + unique_paths(r, c - 1, memo);

	return memo[key];
}

int main(int arc, char** argv) {
	
	std::vector<int> nums = {1, 32, 34, 53, 13, 10, 22};

	std::cout << add_until_100(nums) << std::endl;

	std::unordered_map<int, int> memo = {};
	std::cout << golomb(42, memo) << std::endl;

	std::unordered_map<int2, int, hash> memo2 = {};
	std::cout << unique_paths(3, 7, memo2) << std::endl;
}