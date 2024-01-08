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

	int a, b;

	while (i--) {
		cin >> a;
		cin >> b;

		reduce(a, b);

		while (true) {
			// a moves
			if (b > a) {
				swap(a, b);
			}

			if (a > 0) {
				--a;
			} else {
				cout << "Bob" << endl;
				break;
			}

			// b moves
			if (a > b) {
				swap(a, b);
			}

			if (b > 0) {
				--b;
			} else {
				cout << "Alice" << endl;
				break;
			}
		}
	}

	return 0;
}
