#include <unistd.h>
#include "malloc.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n)
	{
		*ptr++ = 0;
		--n;
	}
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*p_dst;
	unsigned char	*p_src;

	i = 0;
	p_dst = (unsigned char*)dst;
	p_src = (unsigned char*)src;
	while (i < n)
	{
		p_dst[i] = p_src[i];
		++i;
	}
	return (dst);
}

void		*ft_malloc(unsigned int i)
{
	static void		*first_alloc = NULL;
	static void		*last_alloc = NULL;
	void			*p_brk;

	if (!first_alloc)
		first_alloc = sbrk(0);
	p_brk = sbrk(0);
	if (!sbrk(H_size + i * sizeof(char)))
		return (NULL); 
	if (last_alloc)
		ft_memcpy(p_brk, &last_alloc, sizeof(void*));
	else
		ft_bzero(p_brk, sizeof(void*));
	ft_bzero(p_brk + NEXT, sizeof(void*));
	ft_memcpy(p_brk + ADDR, &(((char*)p_brk)[H_size]), sizeof(void*));
	ft_memcpy(p_brk + SIZE, &i, sizeof(int));
	((char*)p_brk)[FLAG] = USED;
	if (last_alloc)
		ft_memcpy(last_alloc + NEXT, &p_brk, sizeof(void*));
	last_alloc = p_brk;
	return (void*)(p_brk + ADDR);
}

void ft_test(char *str)
{

}

int main()
{
	char *str = NULL;

	if (!(str = (char*)ft_malloc(12)))
		write(2, "pas de malloc", 15);
	ft_memcpy(str, "microshell", 11);
	write(1, str, 11);
	return (0);
}





