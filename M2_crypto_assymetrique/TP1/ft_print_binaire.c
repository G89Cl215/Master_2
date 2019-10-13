/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_binaire.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 10:09:22 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/13 10:11:01 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*                                                                            */
/* Fonction d'affichage de nombre en binaire                                  */
/*                                                                            */

void					ft_print_base_bin(unsigned long to_print)
{
	char				ret[65];
	long unsigned int	i;
	int					j;

	i = 1;
	j = 64;
	while (j-- > 0)
		ret[63 - j] = (to_print & i << j) ? '1' : '0';
	ret[64] = '\n';
	write(1, ret, 65);
}
