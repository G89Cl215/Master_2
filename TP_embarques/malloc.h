#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# define H_size		3 * sizeof(void*) + sizeof(unsigned int) + sizeof(char)
# define NEXT		sizeof(void*)
# define ADDR		2 * sizeof(void*)
# define SIZE		3 * sizeof(void*)
# define FLAG		3 * sizeof(void*) + sizeof(unsigned int)

# define USED		0x1
# define FREED		0x0


#endif
