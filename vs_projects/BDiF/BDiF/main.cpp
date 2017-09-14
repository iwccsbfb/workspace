#include "STDFIN_RANDOM_THREEFRY_ENGINE.HPP"
#include <climits>
#include <iostream>
#include <chrono>
#include <random>
#include <thread>

// Needed to time things.
#define START_TIMER  std::chrono::system_clock::time_point t0 = \
std::chrono::system_clock::now();
#define END_TIMER    std::chrono::system_clock::time_point t1 = \
std::chrono::system_clock::now();
#define ELAPSED_TIME \
std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()

static const int NUM_SAMPLES = 100000000;
static const int NUM_THREADS = 10;

struct Point {

private:
	stdfin::threefry_engine rng;

public:
	double x;
	double y;

	Point() {
		rng.seed();
	}

	Point(uint32_t tid) {
		rng.seed((int)tid);
	}

	void next() {
		x = double(rng()) / UINT32_MAX;
		y = double(rng()) / UINT32_MAX;
	}

	int inside_circle() {
		return (((x - 0.5)*(x - 0.5) + (y - 0.5)*(y - 0.5)) < 0.25) ? 1 : 0;
	}
};

static int count[NUM_THREADS];

// Thread function. When a thread is launched, this is the code
// that gets executed.
void ThreadFunction(int threadID, int num) {

	Point p(threadID);

	for (int i = 0; i < num; i++) {

		// Throw a dart at the unit square!
		p.next();
		count[threadID] += p.inside_circle();
	}
}

int main()
{
	double pi = 0.0;

	START_TIMER

		std::thread thread[NUM_THREADS];

	// Launch threads.
	for (int i = 0; i < NUM_THREADS; ++i) {
		thread[i] = std::thread(ThreadFunction, i,
			NUM_SAMPLES / NUM_THREADS);
	}

	std::cout << NUM_THREADS << " threads launched." << std::endl;

	// Join threads to the main thread of execution.
	int total = 0;
	for (int i = 0; i < NUM_THREADS; ++i) {
		thread[i].join();
		total += count[i];
	}

	// Calculating pi
	pi = 4.0 * total / NUM_SAMPLES;

	END_TIMER

		std::cout << "Estimated value of PI (using " << NUM_SAMPLES;
	std::cout << " random samples): " << pi;
	std::cout << " calculated in " << ELAPSED_TIME << " ms";
	std::cout << std::endl << std::endl;

	return 0;
}

// Typical program output is shown below ...
//
// 10 threads launched.
// Estimated value of PI (using 100000000 random samples): 3.14164 calculated in 2471 ms

// Copyright (C) 2013, Andrew J. T. Sheppard, all rights reserved.