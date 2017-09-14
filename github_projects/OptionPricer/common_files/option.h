#ifndef _OPTION_H_
#define _OPTION_H_
#include <cmath>
#define M_PI 3.14159265358979323846 

struct option {
	// price of underlying asset
	double S0;
	// strike value
	double K;
	// maturity
	double T;
	// volatility
	double sigma;
	// divident rate
	double q;
	// risk free interest rate
	double r;
	option() {}
	option(double _S0, double _K, double _T, double _sigma, double _q, double _r)
		:S0(_S0), K(_K), T(_T), sigma(_sigma), q(_q), r(_r) {}

	// the cdf of standard normal random variable
	static double normal_cdf(double value)
	{
		return 0.5 * erfc(-value / (sqrt(2)));
	}

	// get the BS value for european put
	double euro_put_BS() {
		double d1 = (log(S0 / K) + (r - q + sigma*sigma / 2)*T) / (sigma*sqrt(T));
		double d2 = d1 - sigma*sqrt(T);
		return K*exp(-r*T)*normal_cdf(-d2) - S0*exp(-q*T)*normal_cdf(-d1);
	}

	// get the BS value for european call
	double euro_call_BS() {
		double d1 = (log(S0 / K) + (r - q + sigma*sigma / 2)*T) / (sigma*sqrt(T));
		double d2 = d1 - sigma*sqrt(T);
		return S0*exp(-q*T)*normal_cdf(d1) - K*exp(-r*T)*normal_cdf(d2);
	}
};


// derivative type
enum DerType {
	EUR_PUT, EUR_CALL, AME_PUT, AME_CALL
}; 


#endif