/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_Fp_mult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 10:17:01 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/13 10:36:41 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_FP.h"

t_pol_Fp				ft_Fp_mult(t_pol_Fp pol1, t_pol_Fp pol2)
{
	t_pol_Fp	res;
	t_pol_Fp	tmp;
	size_t		deg;
	size_t		i;

	i = 0;
	pol1 = f2_poly_rem(pol1, mod);
	pol2 = f2_poly_rem(pol2, mod);
	tmp = pol1;
	res = UNITE & pol2 ? pol1 : 0;
	deg = f2_poly_deg(pol2);
	while (i < deg)
	{
		i++;
		tmp = f2_poly_rem(tmp << 1, mod);
		if ((UNITE << i) & pol2)
		{
			res ^= tmp;
			res = f2_poly_rem(res, mod);
		}
	}
	return (f2_poly_rem(res, mod));
}
