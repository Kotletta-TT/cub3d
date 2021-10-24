#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*new_s;
	size_t	i;

	i = 0;
	new_s = (char *) s;
	while (i < n)
		new_s[i++] = 0;
}
