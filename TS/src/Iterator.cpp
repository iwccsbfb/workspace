/*
 * Iterator.cpp
 *
 *  Created on: Dec 18, 2016
 *      Author: Zengye
 */

#include <vector>
#include <iostream>
using namespace std;

// - mode 5 iterator
class Iterator {
public:
    Iterator(const vector<int>& nums): _nums(nums) {
    	if(nums.size() > 0)
    		_idx = 0;
    	else
    		_idx = -1;
    }
    // Iterator(const Iterator& iter);
    virtual ~Iterator() {}

    // Returns the next element in the iteration.
    virtual int next() {
		return _nums[_idx++];
	}

    // Returns true if the iteration has more elements.
    virtual bool hasNext() {
		return _idx < _nums.size();
	}
private:
    vector<int> _nums;
	// index of next element
    unsigned int _idx;
};

class ModFiveIterator : public Iterator {
public:
    ModFiveIterator(const vector<int> &nums) : Iterator(nums){
		_has_next = false; 
		_next_ele = 0;
    }

    // Returns the next element in the iteration.
    int next() {
        if (!hasNext())
            throw runtime_error("no more elements!");
		_has_next = false;
        return _next_ele;
    }

    // Returns true if the iteration has more elements.
    bool hasNext() {
		if(_has_next) return true;
        while (Iterator::hasNext()) {
            int n = Iterator::next();
            if (n % 5 == 0) {
                _next_ele = n;
				_has_next = true;
                return true;
            }
        }
        return false;
    }

private:
	bool _has_next = false;
    int _next_ele;
};


int main() {
	vector<int> v{1,2,3,4,5,6,7,8,9,10};
	ModFiveIterator f_it(v);
	try {
		while(f_it.hasNext()) 
			cout << f_it.next() << endl;
		cout << f_it.next() << endl;
	} catch(runtime_error &e) {
		cout << e.what() << endl;
	}
	return 0;
}

