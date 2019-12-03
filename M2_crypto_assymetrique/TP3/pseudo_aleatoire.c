#include <stdint.h>
#include "Rho_Pollard.h"

uint64_t	ft_pseudo_aleatoire(uint64_t Prob[3], uint64_t y, size_t alpha_beta[2])
{
	int		y_mod;

	y_mod = y % 3;
	if (!y_mod)
	{
		alpha_beta[0] *= 2;
		alpha_beta[1] *= 2;
		return ((y * y) % Prob[MOD]);
	}
	if (y_mod == 1)
	{
		alpha_beta[1] += 1;
		return ((y * Prob[H]) % Prob[MOD]);
	}
	alpha_beta[0] += 1;
	return ((y * Prob[G]) % Prob[MOD]);
}
