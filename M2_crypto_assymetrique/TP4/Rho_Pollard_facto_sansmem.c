#include <unistd.h>
#include <stdio.h>
#include <gmp.h>

extern struct _IO_FILE	*stdout;

void	ft_pseudo_aleatoire(mpz_t x, const mpz_t to_factor)
{
	mpz_t	ret;

	mpz_init(ret);
	mpz_mul(ret, x, x);
	mpz_add_ui(ret, ret, 1);
	mpz_mod(ret, ret, to_factor);
	mpz_set(x, ret);
}


void	ft_Rho_Pollard_factorsansmem(mpz_t factor, const mpz_t to_factor)
{
	int		k;
	mpz_t	x1, x2, gcd, sub;

	k = 0;
	mpz_inits(x1, x2, gcd, sub, NULL);
	mpz_set_ui(x1, 1);
	mpz_set_ui(x2, 1);
	while (mpz_cmp(to_factor, x1) > 0)
	{
		ft_pseudo_aleatoire(x1, to_factor);
		mpz_sub(sub, x1, x2);
		mpz_gcd(gcd, sub, to_factor);
		mpz_gcd(gcd, gcd, to_factor);
		if (mpz_cmp_ui(gcd, 1) > 0)
		{
			mpz_set(factor, gcd);
			mpz_clears(x1, x2, gcd, sub, NULL);
			return ;
		}
		k++;
		if (!(k & (k - 1)))
			mpz_set(x2, x1);
	}
}

int		main(int ac, char **av)
{
	mpz_t		to_factor;
	mpz_t		factor;

	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "Factor: wrong number of args.\nShould be one numeric arg.\n");
		return (2);
	}
	mpz_inits(to_factor, factor, NULL);
	mpz_set_str(to_factor, av[1], 10);
	printf("Factor: trying to factor: ");
	mpz_out_str(stdout, 10, to_factor);
	ft_Rho_Pollard_factorsansmem(factor, to_factor);
	printf("\nFactor: we found the factor: ");
	mpz_out_str(stdout, 10, factor);
	printf("\n");
	return (0);
}
