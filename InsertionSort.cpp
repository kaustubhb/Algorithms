#include <cstdlib>
#include <iostream>
#include <fstream>
#include <deque>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

namespace lectures {
	void insertionSort(vector<int> &v) {
		for(size_t i=1;i<v.size();++i) {
			int pivot = v[i];
			size_t j;
			for(j=i-1;j>=0 && pivot < v[j];--j) {
				v[j+1] = v[j];
			}
			v[j+1] = pivot;
		}
	}
}

using namespace lectures;
int main_insertionsort() {
	vector<int> v = {8,2,4,9,7,6};
	insertionSort(v);

	for(auto x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}
