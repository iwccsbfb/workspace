//#include <iostream>
//#include <sstream>
//#include <vector>
//#include <cstdio>
//#include <ctime>
//#include <mpi.h>
//#include "boost_1_59_0/date_time/posix_time/posix_time.hpp"
//#include <cmath>
//using namespace std;
//
//
//void error() {
//	cerr << "something wrong!\n";
//	exit(-1);
//}
//
//// cdf of normal random variable
//double normal_cdf(double value, double mu = 0, double sigma = 1) {
//	return 0.5 * erfc(-(value - mu) / (sigma*sqrt(2.0)));
//}
//
//struct data_row {
//	string str;
//	float price;
//	int amount;
//	long long time_diff; // time interval in milliseconds compared with 1970-1-1
//	data_row(string row) {
//		str = row;
//		auto elems = split(row);
//		amount = stoi(elems[2]);
//		price = stof(elems[1]);
//
//		// deal with time
//		short year, month, day, hour, minute, second;
//		float sec_decimal;
//		auto dt_str = split(elems[0], ':');
//		year = stoi(dt_str[0].substr(0, 4));
//		month = stoi(dt_str[0].substr(4, 2));
//		day = stoi(dt_str[0].substr(6, 2));
//		hour = stoi(dt_str[1]);
//		minute = stoi(dt_str[2]);
//		auto tmp = split(dt_str[3], '.');
//		second = stoi(tmp[0]);
//		sec_decimal = stof("0." + tmp[1]);
//
//		using namespace boost::gregorian;
//		using namespace boost::posix_time;
//		date in_date(year, month, day);
//		time_duration td(hour, minute, second);
//		td += microsec(sec_decimal * 1000000);
//
//		ptime time(in_date, td);
//		// cout << time << endl;
//		ptime time_t_epoch(date(1970, 1, 1));
//		time_duration diff = time - time_t_epoch;
//		time_diff = diff.total_milliseconds();
//	}
//private:
//	std::vector<std::string> split(const std::string &s, char delim = ',') {
//		std::vector<std::string> elems;
//		std::stringstream ss(s);
//		std::string item;
//		while (std::getline(ss, item, delim)) {
//			elems.push_back(item);
//		}
//		return elems;
//	}
//};
//
//// implement < operator
//bool compare(data_row* &a, data_row* &b) {
//	return a->time_diff < b->time_diff;
//}
//
//// global variables
//int num_nodes;
//int id;
//
//void read_block(vector<data_row*> &rows, string f_name) {
//	if (id == 0)
//		cout << "The number of processes involved is: " << num_nodes << "\n\n";
//
//	MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);
//	long long file_size; // int might overflow
//	MPI_File fh;
//	if (MPI_File_open(MPI_COMM_WORLD, f_name.c_str(), MPI_MODE_RDONLY, MPI_INFO_NULL, &fh)) error();
//	if (MPI_File_get_size(fh, &file_size))  error();
//
//	MPI_Status status;
//	// const int window = 20;
//	int chunk_size = file_size / num_nodes;
//	long long start_read_idx, end_read_idx;
//
//	// double check start_idx and end_idx
//	//if (id == 0) start_reading_idx = 0;
//	//else start_reading_idx = chunk_size*id - (window - 1);
//	//if (id == num_nodes - 1) end_reading_idx = chunk_size*(id + 1) - 1;
//	//else end_reading_idx = chunk_size*(id + 1) - 1 + (window - 1);
//
//	std::cout << id << "th node started reading..\n";
//	std::clock_t start = std::clock();
//
//	start_read_idx = chunk_size*id;
//	end_read_idx = start_read_idx + chunk_size;
//	char * data = new char[end_read_idx - start_read_idx + 1];
//	int read_size = end_read_idx - start_read_idx;
//	if (MPI_File_read_at(fh, start_read_idx, data,
//		read_size, MPI_BYTE, &status))
//		error();
//
//	data[read_size] = NULL;
//	stringstream ss(data);
//	string line;
//	// some lines have 39 chars, some have 40 chars
//	rows.reserve(read_size / 39);
//	int cnt = 0;
//
//	while (std::getline(ss, line)) {
//		data_row *row = new data_row(line);
//		rows.push_back(row);
//	}
//
//	double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
//	std::cout << "reading time for node " << id << " : " << duration << '\n';
//}
//
//// store valid data into valid_rec, invalid data into invalid_rec
//// and sort valid_rec;
//void find_valid_data(vector<data_row*> &rows, vector<data_row*> &valid_rec, vector<data_row*> &invalid_rec)
//{
//	int window = 10;
//	for (int i = window; i < rows.size(); i++) {
//		auto &row = rows[i];
//		bool is_valid = true;
//		if (row->price >= 10000 || row->price <= 0 || row->amount <= 0)
//			is_valid = false;
//		else {
//			int vote = 0;
//			for (int inner = i - window; inner < i; inner++)
//				// when time differnce is bigger than 2 seconds
//				if (abs(row->time_diff - rows[inner]->time_diff) >= 2000000) {
//					vote++;
//				}
//			if (vote >= 3) is_valid = false;
//		}
//		if (is_valid) valid_rec.push_back(row);
//		else invalid_rec.push_back(row);
//	}
//
//	// sort the valid_rec by time;
//	// std sort is very fast for almost sorted arrays
//	sort(valid_rec.begin(), valid_rec.end(), compare);
//
//	// do not need to sort invalid data
//	// sort(valid_rec.begin(), valid_rec.end(), compare);
//}
//
//void get_returns(vector<data_row*> &valid_rec, vector<double> &ret) {
//	int sz = valid_rec.size();
//	ret.reserve(sz - 1);
//	for (int i = 1; i < sz; i++) {
//		double val = fabs(valid_rec[i]->price - valid_rec[i - 1]->price) / valid_rec[i - 1]->price;
//		ret.push_back(val);
//	}
//}
//
//// run Kolmogorov-Smirnov normality_test
//bool NORMAL(vector<double> &ret) {
//	int N = ret.size();
//	double sum = 0, mu, sigma;
//	for (auto &i : ret)
//		sum += i;
//	mu = sum / N;
//	sum = 0;
//	for (auto &i : ret)
//		sum += (i - mu)*(i - mu);
//	sigma = sqrt(sum / N);
//	// the Kolmogorov-Smirnov statistic
//	double D = 0;
//	for (int i = 1; i < ret.size(); i++) {
//		double F = normal_cdf(ret[i], mu, sigma);
//		D = max(F - (i - 1) / N, i / N - F);
//	}
//	// the ks-statistic benchmark of appha = 0.05
//	double benchmark = 1.36 / sqrt(N);
//	if (D > benchmark)return false;
//	else return true;
//}
//
//void output_data(vector<data_row*> &valid_rec, string f_name) {
//	int num_nodes;
//	MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);
//	MPI_File handle;
//	int ret = MPI_File_open(MPI_COMM_WORLD, f_name.c_str(), MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &handle);
//
//	// get file content;
//	long long size = 0;
//	for (auto &row : valid_rec)
//		size += row->str.size() + 1;
//	char *data = new char[size], *p = data;
//	memset(data, 0, size);
//	for (auto &row : valid_rec) {
//		string tmp = row->str + '\n';
//		strcpy(p, tmp.c_str());
//		//strcpy_s(p, tmp.size(), tmp.c_str());
//		p += tmp.size();
//	}
//	long long * all_sz_arr = new long long[num_nodes];
//	MPI_Allgather(&size, 1, MPI_LONG_LONG, all_sz_arr, 1, MPI_LONG_LONG, MPI_COMM_WORLD);
//	long long all_sz = 0;
//	// change all_sz_arr to accumulative size array
//	for (int i = 1; i < num_nodes; i++)
//		all_sz_arr[i] += all_sz_arr[i - 1];
//	all_sz = all_sz_arr[num_nodes - 1];
//	ret |= MPI_File_set_size(handle, all_sz); // ?
//	MPI_Status status;
//	ret |= MPI_File_write_at_all(handle, all_sz_arr[id] - size, (void*)data, size, MPI_BYTE, &status);
//	if (ret) error();
//	MPI_File_close(&handle);
//}
//
//int main(int argc, char *argv[]) {
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);
//	MPI_Comm_rank(MPI_COMM_WORLD, &id);
//
//	// reading file blocks
//	vector<data_row*> rows;
//	read_block(rows, "data10k.csv");
//
//
//	std::clock_t start = std::clock();
//	// valid records, and invalid records;
//	vector<data_row*> valid_rec, invalid_rec;
//	find_valid_data(rows, valid_rec, invalid_rec);
//
//	// get vector of returns
//	vector<double> ret;
//	get_returns(valid_rec, ret);
//
//	// return's normality test;
//	if (NORMAL(ret))
//		cout << "the returns are accepted as normal at node " << id << "\n";
//	else
//		cout << "the returns are NOT accepted as normal at node " << id << "\n";
//
//	double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
//	std::cout << "Processing time for node " << id << " : " << duration << '\n';
//	
//	start = std::clock();
//	output_data(valid_rec, "signal.txt");
//	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
//	std::cout << "Time used to write signal.txt at node" << id << " : " << duration << '\n';
//
//	start = std::clock();
//	output_data(invalid_rec, "noise.txt");
//	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
//	std::cout << "Time used to write noise.txt at node" << id << " : " << duration << '\n';
//
//	MPI_Finalize();
//}

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

	int myid, nprocs;

	long int npts = 1e8;

	long int i, mynpts;

	double f, sum, mysum;
	double xmin, xmax, x;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	if (myid == 0) {
		mynpts = npts - (nprocs - 1)*(npts / nprocs);
	}
	else {
		mynpts = npts / nprocs;
	}

	mysum = 0.0;
	xmin = 0.0;
	xmax = 1.0;

	srand(myid);

	for (i = 0; i<mynpts; i++) {
		x = (double)rand() / RAND_MAX*(xmax - xmin) + xmin;
		mysum += 4.0 / (1.0 + x*x*x);
	}

	MPI_Reduce(&mysum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myid == 0) {
		f = sum / npts;
		printf("PI calculated with %ld points = %f \n", npts, f);
	}

	MPI_Finalize();
}