#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

class Solution {
public:
	int removeElement(vector<int>& nums, int val) {

		int c = 0;  //count

		for (int i = 0; i < nums.size(); ++i) {
			if (nums[i] != val) {
				nums[c] = nums[i];
				++c;
			}
		}

		return c;
	}
};

int main(int argc, char** argv) {

	Solution s = Solution();

	vector<int> v1 = {0,1,2,2,3,0,4,2};

	cout << s.removeElement(v1, 2) << std::endl;

	for (auto i : v1) {
		cout << i << ", " << endl;
	}

	return 0;
}
