/*
 * Iterator.cpp
 *
 *  Created on: Dec 18, 2016
 *      Author: Zengye
 */

#include "header.h"


// iterator: implement : operation???

// - mode 5 iterator
class Iterator {
public:
    Iterator(const vector<int>& nums);
    // Iterator(const Iterator& iter);
    virtual ~Iterator();
    // Returns the next element in the iteration.
    int next();
    // Returns true if the iteration has more elements.
    bool hasNext();
    void remove();
};

class ModFiveIterator : public Iterator {
public:
    ModFiveIterator(const vector<int> &nums) : Iterator(nums){
        nextEle = 1; // can be any number
    }

    // Returns the next element in the iteration.
    int next() {
        if (!hasNext())
            throw runtime_error("no more elements!");

        return nextEle;
    }

    // Returns true if the iteration has more elements.
    bool hasNext() {
        while (Iterator::hasNext()) {
            int n = Iterator::next();
            if (n % 5 == 0) {
                nextEle = n;
                return true;
            }
        }
        return false;
    }

    void remove(){
        Iterator::remove();
    }

private:
    int nextEle;
};
