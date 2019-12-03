#ifndef RHO_POLLARD_H
# define RHO_POLLARD_H

# include <stdint.h>
# include <stdio.h>
# include <string.h>

# define Y_0	1
# define MOD	0	
# define G		1
# define H		2

uint64_t	ft_pseudo_aleatoire(uint64_t Prob[3], uint64_t y, size_t alpha_beta[2]);

#endif
