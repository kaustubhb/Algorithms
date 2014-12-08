#include <cstdlib>
#include <iostream>
#include <fstream>
#include <deque>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

namespace lectures {

	void merge(vector<int> &v, int beg, int mid, int end);
	void mergeSort_r(vector<int> &v, int beg, int end);

	void mergeSort(vector<int> &v) {
		mergeSort_r(v,0,v.size()-1);
	}

	void mergeSort_r(vector<int> &v, int beg, int end) {
		if(beg == end) return;

		int mid = (beg+end)/2;
		mergeSort_r(v, beg,mid);
		mergeSort_r(v, mid+1,end);

		merge(v, beg, mid, end);
	}

	void merge(vector<int> &v, int beg, int mid, int end) {
		int i=beg,j=mid+1;
		vector<int> merged;
		while(i<=mid && j<=end) {
			if(v[i] <= v[j]) {
				merged.push_back(v[i]);
				++i;
			}
			else {
				merged.push_back(v[j]);
				++j;
			}
		}
		while(i<=mid) {
			merged.push_back(v[i]);
			++i;
		}
		while(j<=end) {
			merged.push_back(v[j]);
			++j;
		}

		// now copy back to v
		for(i=0;i<merged.size();++i) {
			v[beg+i] = merged[i];
		}
	}
}

using namespace lectures;
int main() {
	vector<int> v = {8,2,4,9,7,6};
	mergeSort(v);

	for(auto x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}
