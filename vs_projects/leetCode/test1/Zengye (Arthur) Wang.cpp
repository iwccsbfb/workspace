/*
author: Zengye (Arthur) Wang
2015-11-16
*/

#include<vector>
using namespace std;

// for quick sort
size_t partition(vector<int> &v, int s, int e) {
	int pivot = v[e];
	int i = s;
	for (int j = s; j <= e - 1; j++) {
		if (v[j] < pivot) {
			std::swap(v[i], v[j]);
			i++;
		}
	}
	std::swap(v[i], v[e]);
	return i;
}

void quicksort(vector<int> &v, int start, int end) {
	if (start >= end) return;
	size_t p = partition(v, start, end);
	quicksort(v, start, p - 1);
	quicksort(v, p + 1, end);
}

void quicksort(vector<int> &v) {
	quicksort(v, 0, v.size() - 1);
}

class myheap {
public:
	myheap(){}
	myheap(vector<int> &v2) {
		v = v2;
		heapfy(v);
	}

	// add an element to the heap
	void Add(int a) {
		v.push_back(a);
		sift_up(v, v.size() - 1);
	}

	// pop the max element from the heap
	void Pop() {
		if (v.empty())	return;
		v[0] = v[v.size() - 1];
		v.pop_back();
		sift_down(v, 0, v.size() - 1);
	}

	// remove an element from the heap, if it doesn't exist, return false
	bool Remove(int a) {
		for (int i = 0; i < v.size(); i++) {
			if (v[i] == a) {
				v[i] = std::numeric_limits<int>::max();
				sift_up(v, i);
				v[0] = v[v.size() - 1];
				v.pop_back();
				sift_down(v, 0, v.size() - 1);
				return true;
			}
		}
		return false;
	}


private:
	vector<int> v;

	void heapfy(vector<int> &v) {
		int size = v.size();
		for (int i = (size - 2) / 2; i >= 0; i--)
			sift_down(v, i, size - 1);
		//sift_up(v, i);
	}

	// end is the end of v; sift the begin down to end
	void sift_down(vector<int> &v, int begin, int end) {
		int i = begin, swap = i;
		int child = i * 2 + 1;
		while (child <= end) {
			if (child + 1 <= end && v[child] < v[child + 1])
				swap = child + 1;
			else if (v[i] < v[child])
				swap = child;
			if (swap == i)
				return;
			std::swap(v[swap], v[i]);
			i = swap;
			child = i * 2 + 1;
		}
	}

	// i means the index to be sifted up, 0 to i-1 are already a heap
	// this is a max heap
	void sift_up(vector<int> &v, int i) {
		int father = (i - 1) / 2;
		while (i != 0) {
			if (v[father] < v[i])
				std::swap(v[father], v[i]);
			i = father;
			father = (i - 1) / 2;
		}
	}


};

int main() {
	vector<int> v{ 5, 4, 6, 8, 7, 9 };

	myheap h(v), h2;
	h.Add(10);
	h.Remove(4);
	h.Remove(10);
	h.Add(20);
	h.Pop();
	h.Pop();

	h2.Add(3);
	h2.Add(10);
	h2.Add(12);
	h2.Add(13);


	vector<int> v2{ 5, 4, 6, 8, 7, 9, 1, 2, 3 };
	quicksort(v2);

	return 0;
}

