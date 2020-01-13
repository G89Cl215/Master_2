#include <unistd.h>
#include <stdio.h>
#include <gmp.h>

extern struct _IO_FILE	*stdout;

void	ft_pseudo_aleatoire(mpz_t x, const mpz_t to_factor)
{
	mpz_mul(x, x, x);
	mpz_add_ui(x, x, 1);
	mpz_mod(x, x, to_factor);
}

/*
** WARNING : This algorithm may never ever return !!! So make sure the number
** to_factor, you want to factor, is composite (if it's prime, you can keep on
** trying to factor it for a looooong time).
*/

void	ft_Rho_Pollard_factorsansmem(mpz_t factor, const mpz_t to_factor)
{
	int		k;
	mpz_t	x1, x2, gcd;

	k = 0;
	mpz_inits(x1, x2, gcd, NULL);
	mpz_set_ui(x1, 1);
	mpz_set_ui(x2, 1);
	while (mpz_cmp(to_factor, x1) > 0)
	{
		ft_pseudo_aleatoire(x1, to_factor);
		mpz_sub(gcd, x1, x2);
		mpz_gcd(gcd, gcd, to_factor);
		if (mpz_cmp_ui(gcd, 1) > 0)
		{
			mpz_set(factor, gcd);
			mpz_clears(x1, x2, gcd, NULL);
			return ;
		}
		k++;
		if (!(k & (k - 1)))
			mpz_set(x2, x1);
	}
}

/*
** This program reads the first argument that should be a COMPOSITE number
** expressed in base 10, and returns a factor of this composite number.
*/

int		main(int ac, char **av)
{
	mpz_t		to_factor;
	mpz_t		factor;
	mpz_t		q;
	mpz_t		r;

	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "Factor: wrong number of args.\nShould be one numeric arg.\n");
		return (2);
	}
	mpz_inits(to_factor, factor, q, r, NULL);
	mpz_set_str(to_factor, av[1], 10);
	printf("Factor: trying to factor: ");
	mpz_out_str(stdout, 10, to_factor);
	ft_Rho_Pollard_factorsansmem(factor, to_factor);
	printf("\nFactor: we found the factor: ");
	mpz_out_str(stdout, 10, factor);
	printf("\nFactor: Decomposed number: ");
	mpz_out_str(stdout, 10, factor);
	printf(" * ");
	mpz_fdiv_qr(q, r, to_factor, factor);
	mpz_out_str(stdout, 10, q);
	printf("\nFactor: Error check: And the rest is: ");
	mpz_out_str(stdout, 10, r);
	printf("\n");
	return (0);
}
