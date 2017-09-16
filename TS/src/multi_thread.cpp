#include "header.h"

// - 给你两个independent queue，每个queue都存着timestamp，只能有getNext()来取queue里面的timestamp，每个timestamp只能被取一次，比较这两个queue里的timestamp，如果差值<1，print这两个timestamp。例如：
//Q1 0.2, 1.4, 3.0
//Q2 1.0 1.1, 3.5
//output: (0.2, 1.0), (1.4, 1.0), (0.2, 1.1), (1.4, 1.1), (3.0, 3.5)
//最后用了两个thread,两个thread-safe queue来实现. 每次call getNext(), 和另一个queue里存的每个item相比, 相差大于一就删除, 否则输出
//https://www.ibm.com/developerworks/cn/aix/library/au-multithreaded_structures1/
#include <string>
#include <iostream>
#include <deque>
#include <mutex>
#include <thread>

using namespace std;

// this is the final result containing timestamp pairs < 1
vector<pair<double, double> > result;
// queue defined to stored numbers from streams
deque<double> Q1; // use list so we can iterate
deque<double> Q2;
// the lock shared between threads
std::mutex mymutex;


class Stream{
	vector<int> data;
	unsigned int idx = 0;
public:
	Stream(vector<int> &rhs) {
		data = rhs;
	}
	int getNext() {
		// if reaches end, throw exception
		return data[idx++];
	}
};

// this is a utility function
void calculate( deque<double> &q, double val) {
	while (!q.empty() && val - q.front() > 1)
		q.pop_front();
	for (double num : q) {
		if (abs(val - num) <= 1)
			result.push_back(make_pair(val, num));
		else break;
	}
}

// function that will be executed by thread 1
void task1(Stream &s) {
    while (true) {
        double val = s.getNext();
        mymutex.lock();
        Q1.push_back(val);
        calculate(Q2, val);
        mymutex.unlock();
    }
}

// function that will be executed by thread 2
void task2(Stream &s) {
    while (true) {
        double val = s.getNext();
        mymutex.lock();
        Q2.push_back(val);
        calculate(Q1, val);
        mymutex.unlock();
    }
}


void run_multi_thread()
{
    // incoming streams
	vector<int> data1 = {0.2, 1.4, 3.0};
    Stream S1 (data1);
	vector<int> data2 = {2.0, 2.1, 4.5};
    Stream S2 (data2);

    // create the threads
    std::thread t1(task1, std::ref(S1));
    std::thread t2(task2, std::ref(S2));

    // start the threads
    t1.join();
    t2.join();
}
