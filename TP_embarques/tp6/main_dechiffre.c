#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int ac, char **av)
{
		int			fd;
		char		rd;
		int			i, j;
		int			stop = 2;
		char		data;

		if (ac < 2 || (fd = open(av[1], O_RDONLY)) < 0)
			return (0);
		i = 0;
		while(read(fd, &rd, 1) > 0)
		{
				i = 0;
				while (i < 8)
				{
						if (((rd >> i) & 1) == 0)
						{
								j = 0;
								data = 0;
								while (j < 8)
								{
										if (i < 7)
												i++;
										else
										{
												i = 0;
												read(fd, &rd, 1);
										}
										data |= (((rd >> i) & 1)) << j;
										j++;
								}
								printf("%c", data, data);
								i += 2;
						}
						i++;

				}

		}
}
