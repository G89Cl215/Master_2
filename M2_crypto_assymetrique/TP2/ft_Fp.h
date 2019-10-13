/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_Fp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 10:17:48 by tgouedar          #+#    #+#             */
/*   Updated: 2019/10/13 10:36:41 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FP_H
# define FT_FP_H

#ifndef DEG
# define DEG		5
#endif

typedef uint64_t		t_pol_Fp[DEG];

uint64_t				ft_inv_modp(uint64_t elem, uint64_t prime);

t_pol_Fp				ft_Fp_mult(t_pol_Fp, t_pol_Fp, uint64_t prime, t_pol_Fp mod);

#endif
