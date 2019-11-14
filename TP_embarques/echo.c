#include <unistd.h>

unsigned int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int				main(int ac, char *av[])
{
	unsigned int	i;

	i = 0;
	while (++i < ac)
	{
		write(1, av[i], ft_strlen(av[i]));
		if (av[i + 1])
			write(1, " ", 1);
		else	
			write(1, "\n", 1);
	}
	return (0);
}
