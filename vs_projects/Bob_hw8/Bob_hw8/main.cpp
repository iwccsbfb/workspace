#include <iostream>
#include <fstream>
using namespace std;


double normal_cdf(double value)
{
	return 0.5 * erfc(-value / (sqrt(2)));
}
# define M_PI 3.14159265358979323846 

double euro_call_BS(double S0, double K, double T, double sigma, double q, double r) {
	double d1 = (log(S0 / K) + (r - q + sigma*sigma / 2)*T) / (sigma*sqrt(T));
	double d2 = d1 - sigma*sqrt(T);
	return S0*exp(-q*T)*normal_cdf(d1) - K*exp(-r*T)*normal_cdf(d2);
}

//	df/d(sigma) vega for put and call
double euro_vega(double S0, double K, double T, double sigma, double q, double r) {
	double d1 = (log(S0 / K) + (r - q + sigma*sigma / 2)*T) / (sigma*sqrt(T));
	double vega1 = sqrt(T / (2 * M_PI))*S0*exp(-q*T - d1*d1 / 2);
	double d2 = d1 - sigma*sqrt(T);
	double vega2 = sqrt(T / (2 * M_PI))*K*exp(-r*T - d2*d2 / 2);
	double tmp = vega1 - vega2;

	return vega1;

}

double euro_put_BS(double S0, double K, double T, double sigma, double q, double r) {
	double d1 = (log(S0 / K) + (r - q + sigma*sigma / 2)*T) / (sigma*sqrt(T));
	double d2 = d1 - sigma*sqrt(T);
	return K*exp(-r*T)*normal_cdf(-d2) - S0*exp(-q*T)*normal_cdf(-d1);
}

double implied_vol_call(double C0, double S0, double K, double T, double q, double r) {
	double x0 = .25, x_new = x0, x_old = x0 - 1, tol = pow(10, -6);
	while (abs(x_new - x_old) > tol) {
		x_old = x_new;
		x_new -= (euro_call_BS(S0, K, T, x_new, q, r) - C0) / euro_vega(S0, K, T, x_new, q, r);
	}
	return x_new;
}

double implied_vol_put(double P0, double S0, double K, double T, double q, double r) {
	double x0 = .25, x_new = x0, x_old = x0 - 1, tol = pow(10, -6);
	while (abs(x_new - x_old) > tol) {
		x_old = x_new;
		double tmp = euro_put_BS(S0, K, T, x_new, q, r),
			tmp2 = euro_vega(S0, K, T, x_new, q, r);
		x_new -= (tmp - P0) / tmp2;
	}
	return x_new;
}

void main() {
	cout << sizeof(double) << endl;
	double S0 = 45, q = .005, r = 0.025, T = .25, K = 50, sigma = .35;
	cout << "question1: call price is: " << euro_call_BS(S0, K, T, sigma, q, r) << endl;
	K = 40, T = .25, sigma = .45;
	cout << "question2: put price is: " << euro_put_BS(S0, K, T, sigma, q, r) << endl;
	double C0, P0;
	K = 50, T = .5, C0 = 2.45;
	cout << "question3, implied vol of call is: " << implied_vol_call(C0, S0, K, T, q, r) << endl;
	K = 30, T = .5, P0 = .8;
	cout << "question4, implied vol of put is: " << implied_vol_put(C0, P0, K, T, q, r) << endl;
}

