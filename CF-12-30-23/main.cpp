#include <iostream>      
#include <cstdio>        
#include <cmath>         
#include <algorithm>     
#include <vector>        
#include <set>           
#include <map>           
#include <unordered_set> 
#include <unordered_map> 
#include <queue>         
#include <stack>         
#include <string>        
#include <cstring>       
//#include "alg.hpp"

using namespace std;

class Solution {
private:
	map<int, int> fill_freq(vector<int>& nums) {
		map<int, int> freq;

		for (auto num : nums) {

			auto it = freq.find(num);

			if (it != freq.end()) {
				it->second += 1;
			} else {
				freq.emplace(num, 1);
			}
		}

		return freq;
	}

public:
	vector<int> frequencySort(vector<int>& nums) {
		auto freq = fill_freq(nums);

		sort(nums.begin(), nums.end(), [&freq](int a, int b) {
			auto it_a = freq.find(a);
			auto it_b = freq.find(b);

			if (it_a != freq.end() && it_b != freq.end()) {
				if (it_a->second > it_b->second) {
					return true;
				}
			}

			return (a < b);
		});
	}
};

void reduce (int &a, int &b, int in = 9) {

	for (int factor = in; factor <= 11; factor++) {
		if (a % factor == 0 && b % factor == 0) {
			a /= factor;
			b /= factor;
			reduce(a, b, factor);
		}
	}

	return;
}

int main() {

	// improves performance of streams
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	// read an integer
	int i;
	cin >> i;

	return 0;
}
