// This is the text editor interface. 
// Anything you type or change here will be seen by the other person in real time.

// 2017-8-24

/*
1. Ask the candidate to design a data structure to hold objects with a corresponding integer weight. It should support:
    Obtain an object randomly with probability equal to (weight of the element) / (sum of the weights).
    Set an object-weight pair. If the object is already in the structure, its weight will be updated. Otherwise, the object will be inserted and set to its weight. If the weight is zero, the object can be removed.
*/


#include <vector> 
#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <string>
using namespace std;
// space: O(n)
// time: set_weight: O(1)
//      get_item: O(n)
class RandomString {
    unordered_map<string, unsigned int> m;
    unsigned long long total_weights;
public: 
    RandomString(): total_weights(0) {}
    void set_weight(string obj, unsigned int weight) {
        if(weight == 0) {
            if(m.find(obj) != m.end()) {
                total_weights -= m[obj];
                m.erase(obj);
            }
            return;
        }
        // if obj is in the map
        if(m.find(obj) != m.end()) 
            total_weights += weight - m[obj];
        else // if obj is not in the map
            total_weights += weight;
        m[obj] = weight;
    }
    
    string get_item() {
        if(total_weights == 0) throw string("no item yet");
        unsigned long long threshold = rand() % total_weights + 1;
        unsigned long long tmp_sum = 0; // the cumulative distribution 
        for(auto & kv: m)  {
            tmp_sum += kv.second;
            if(tmp_sum >= threshold)
                return kv.first;
        }
        cerr << "threshold: " << threshold 
            << "; total_weights:" << total_weights 
            << "; tmp_sum:" << tmp_sum << endl;
        throw string("unexpected error");
    }
};

void test_get_items(RandomString &rs, int n = 100000) {
    cout << "starting get items..." << endl;
    unordered_map<string, int> m;
    for(int i=0; i<n; i++) {
        m[rs.get_item()] ++;
        //cout<< rs.get_item() << ' ';
    }
    for(auto &kv: m) 
        cout << kv.first << " has " << kv.second / float(n) << " probabilty" << endl;
    cout << endl;
}


int main() {
    try{
        RandomString rs;
        test_get_items(rs);
        rs.set_weight("a", 2);
        test_get_items(rs);
        rs.set_weight("b", 3);
        test_get_items(rs);
        rs.set_weight("a", 0);
        test_get_items(rs);
        rs.set_weight("a", 2); 
        rs.set_weight("c", 2);
        test_get_items(rs);
    } catch (string err) {
        cerr << err << endl;
    }
    return 0;
}

