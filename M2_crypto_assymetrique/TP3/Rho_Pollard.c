#include "Rho_Pollard.h"

int		ft_usage(void)
{
	printf("Rho_Pollard: Usage: ./Rho_Pollard Modulus Generator Disc_log\nAll arguments must b positive integers.\n");
	return (-1);
}

int		ft_isdigit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

uint64_t	ft_atoul(char *str)
{
	uint64_t	res;
	size_t	i;

	i = 0;
	res = 0;
	while (str[i])
	{
		res = str[i] - '0' + res * 10;
		i++;
	}
	return (res);
}

uint64_t	ft_inverse_mod(uint64_t to_invert, uint64_t mod)
{
	uint64_t	i = 1;

	while (i < mod)
	{
		if (((to_invert * i) % mod) == 1)
			return (i);
		i++;
	}
	return (0);
}

int			main(int ac, char **av)
{
	uint64_t	Prob[3];
	uint64_t	y_i;
	uint64_t	y_2i;
	size_t		alb_i[2];
	size_t		alb_2i[2];

	if (ac != 4 || !ft_isdigit(av[1])
	|| !ft_isdigit(av[2]) || !ft_isdigit(av[3]))
		return (ft_usage());
	Prob[MOD] = ft_atoul(av[1]);
	Prob[G] = ft_atoul(av[2]);
	Prob[H] = ft_atoul(av[3]);
	//ici verif d'erreur ?
	printf("Parametres du probleme:\nGroupe: |F*_%lu\nGenerateur: %lu\nLog: %lu\n", Prob[MOD], Prob[G], Prob[H]);
	alb_i[0] = 0;
	alb_i[1] = 0;
	y_i = ft_pseudo_aleatoire(Prob, Y_0, alb_i);
	alb_2i[0] = alb_i[0];
	alb_2i[1] = alb_i[1];
	y_2i = ft_pseudo_aleatoire(Prob, y_i, alb_2i);
	while (y_i != y_2i)
	{
		y_i = ft_pseudo_aleatoire(Prob, y_i, alb_i);
		y_2i = ft_pseudo_aleatoire(Prob, y_2i, alb_2i);
		y_2i = ft_pseudo_aleatoire(Prob, y_2i, alb_2i);
	}
	printf("Collision !!!\nLe logarithme discret recherche est : %lu\n", ((alb_2i[0] - alb_i[0]) * ft_inverse_mod(alb_i[1] - alb_2i[1], Prob[MOD])) % Prob[MOD]);
	return (0);
}
