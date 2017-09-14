#include "sorting.h"
#include <vector>
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


// for heap sort


// i means the index to be sifted up, 0 to i-1 are already a heap
// this is a max heap
//void sift_up(vector<int> &v, int i) {
//	int father = (i - 1) / 2;
//	while (i != 0) {
//		if (v[father] < v[i])
//			std::swap(v[father], v[i]);
//		i = father;
//		father = (i - 1) / 2;
//	}
//}

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
//void sift_down(vector<int> &v, int begin, int end) {
//	int i = begin;
//	int l_child = 2 * i + 1, r_child = 2 * i + 2;
//	// when its two childs are within scope
//	while (r_child <= end) {
//		// when r child is bigger
//		if (v[r_child] > v[l_child] && v[r_child] > v[i]) {
//			std::swap(v[r_child], v[i]);
//			i = r_child;
//		}
//		// when l child is bigger
//		else if (v[l_child] > v[r_child] && v[l_child] > v[i]) {
//			std::swap(v[l_child], v[i]);
//			i = l_child;
//		}
//		l_child = 2 * i + 1;
//		r_child = 2 * i + 2;
//	}
//	if (l_child <= end && v[l_child] > v[i])
//		std::swap(v[l_child], v[i]);
//}

void heapfy(vector<int> &v) {
	int size = v.size();
	for (int i = (size - 2) / 2; i >= 0; i--)
		sift_down(v, i, size - 1);
	//sift_up(v, i);
}

// use sift_down for heapfy, which is faster
void heap_sort(vector<int> &v) {
	heapfy(v);
	int end = v.size() - 1;
	while (end > 0) {
		std::swap(v[0], v[end]);
		end--;
		sift_down(v, 0, end);
	}
}

// add bool swaped; to make best use case to be O(n)
template<typename T>
void bubble_sort(vector<T> &v) {
	int size = v.size();
	bool swaped = true;
	for (int i = size - 2; i >= 0 && swaped; i--) {
		swaped = false;
		for (int j = 0; j <= i; j++) {
			if (v[j] > v[j + 1]) {
				std::swap(v[j], v[j + 1]);
				swaped = true;
			}
		}
	}
}

template<typename T>
void insertion_sort(vector<T> & v) {
	size_t size = v.size();
	for (int i = 1; i < size; i++) {
		T tmp = v[i];
		int j;
		for (j = i - 1; j >= 0; j--) {
			if (v[j] > tmp)
				v[j + 1] = v[j];
			else break;
		}
		v[j + 1] = tmp;
	}
}

//template<typename T>
//vector<T> merge_sort_helper(vector<T> &v, size_t s, size_t e) {
//	if (s >= e)	return v;
//	size_t mid = (s + e) / 2;
//	merge_sort_helper(v, s, mid);
//	merge_sort_helper(v, mid + 1, e);
//}

template<typename T>
vector<T> merge_sort_helper(vector<T> &v, int s, int e) {
	if (s == e) 
		return vector<T>({ v[s] });
	int mid = (s + e) / 2;
	vector<T> v1 = merge_sort_helper(v, s, mid);
	vector<T> v2 = merge_sort_helper(v, mid + 1, e);
	size_t i = 0, j = 0;
	vector<T> result;
	while (i < v1.size() && j < v2.size()) {
		if (v1[i] < v2[j]) {
			result.push_back(v1[i]);
			i++;
		}
		else {
			result.push_back(v2[j]);
			j++;
		}
		if (i == v1.size()) {
			for (; j < v2.size(); j++)
				result.push_back(v2[j]);
		}
		if (j == v2.size()) {
			for (; i < v1.size(); i++)
				result.push_back(v1[i]);
		}
	}
	return result;
}

template<typename T>
void merge_sort(vector<T> &v) {
	v = merge_sort_helper(v, 0, v.size() - 1);
}

template<typename T, size_t size>
void binary_search(T v[size]) {

}

void test_sort() {
	//vector<int> v{ 5, 4, 6, 8, 7, 9 };
	//quicksort(v);
	vector<int> v2{ 5, 4, 6, 8, 7, 9, 1, 2, 3 };
	//merge_sort(v2);
	//heap_sort(v2);
	//bubble_sort(v2);
	//insertion_sort(v2);
}
