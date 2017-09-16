/*
 * Iterator.cpp
 *
 *  Created on: Dec 18, 2016
 *      Author: Zengye
 */

#include "header.h"


// - mode 5 iterator
class Iterator {
public:
    Iterator(const vector<int>& nums);
    // Iterator(const Iterator& iter);
    virtual ~Iterator();
    // Returns the next element in the iteration.
    virtual int next();
    // Returns true if the iteration has more elements.
    bool hasNext();
};

class ModFiveIterator : public Iterator {
public:
    ModFiveIterator(const vector<int> &nums) : Iterator(nums){
		has_next = false; 
		next_ele
    }

    // Returns the next element in the iteration.
    int next() {
        if (!hasNext())
            throw runtime_error("no more elements!");
		
        return next_ele;
    }

    // Returns true if the iteration has more elements.
    bool hasNext() {
		if(has_next) return true;
        while (Iterator::hasNext()) {
            int n = Iterator::next();
            if (n % 5 == 0) {
                next_ele = n;
				has_next = true;
                return true;
            }
        }
        return false;
    }

private:
	bool has_next = false;
    int next_ele;
};


int main() {
	
	return 0;
}

