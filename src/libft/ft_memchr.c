#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*new_s;
	unsigned char	new_c;

	i = 0;
	new_c = (unsigned char) c;
	new_s = (unsigned char *) s;
	while (i < n)
	{
		if (new_s[i] == new_c)
			return (new_s + i);
		i++;
	}
	new_s = 0;
	return (new_s);
}
