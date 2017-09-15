#include "tree_pricer.h"
#include <assert.h>
#include <vector>
#include <cmath>

double tirnomial_tree_pricer::get_instrinsic_value(double St, DerType der_type, option &op) {
	switch (der_type)
	{
	case EUR_PUT:
	case AME_PUT:
		return fmax(op.K - St, 0);
	case AME_CALL:
	case EUR_CALL:
		return fmax(St - op.K, 0);
	}
}

double tirnomial_tree_pricer::calculate(int steps, DerType der_type, option &op)
{
	vector<double> V(2 * steps + 1);

	double delta_t, u, d, p_u, p_d, p_m;
	delta_t = op.T / steps;
	u = exp(op.sigma * sqrt(3 * delta_t));
	d = 1 / u;
	p_u = 1 / 6.0 + (op.r - op.q - op.sigma*op.sigma / 2) * sqrt(delta_t / (12 * op.sigma*op.sigma));
	p_d = 1 / 6.0 - (op.r - op.q - op.sigma*op.sigma / 2) * sqrt(delta_t / (12 * op.sigma*op.sigma));
	p_m = 2 / 3.0;

	// set values at maturity
	for (int i = 0; i <= 2 * steps; ++i)
	{
		double St = op.S0*pow(u, steps - i);
		V[i] = get_instrinsic_value(St, der_type, op);
	}

	// calculate backwards
	for (int i = steps - 1; i >= 0; --i)
	{
		for (int j = 0; j <= 2 * i; ++j)
		{
			V[j] = exp(-delta_t*op.r)*(p_u*V[j] + p_m*V[j + 1] + p_d*V[j + 2]);
			// for American options
			if (der_type == AME_CALL || der_type == AME_PUT) {
				double St = op.S0 * pow(u, i - j);
				double tmp_intr_val = get_instrinsic_value(St, der_type, op);
				V[j] = fmax(tmp_intr_val, V[j]);
			}
		}
	}
	return V[0];
}
