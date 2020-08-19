#include "stc++.h"

using namespace std;

/* construct heap */
class Heap{
private:
	vector<int> arr;
	int size = 0;
	bool type = true;

	int getLNode(int i) { return 2 * i + 1; }
	int getRNode(int i) { return 2 * i + 2; }

	void adjustHeap(int father) {
		int lnode = getLNode(father);
		int rnode = getRNode(father);
		int tmp = father;
		if (lnode < size && (arr[tmp] < arr[lnode]) == type) {
			tmp = lnode;
		}
		if (rnode < size && (arr[tmp] < arr[rnode]) == type) {
			tmp = rnode;
		}
		if (tmp != father) {
			swap(arr[tmp], arr[father]);
			adjustHeap(tmp);
		}
	}

public:

	vector<int> getHeap() {
		return arr;
	}

	Heap() {
		size = 0;
	}

	Heap(vector<int> items) {
		arr = items;
		size = items.size();
		for (int i = size/2; i >= 0; i--) {
			adjustHeap(i);
		}
	}

	Heap(vector<int> items, bool t) { 
		arr = items;
		size = items.size();
		type = t;
		for (int i = size/2; i >= 0; i--)
			adjustHeap(i);
	}

};


//int main() {
//	vector<int> test{10,9,8,7,6,5,4,3,2,1};
//	Heap heap(test, false);
//	vector<int> arr = heap.getHeap();
//	for (auto num : arr)
//		cout << num << " : ";
//	return 0;
//}

