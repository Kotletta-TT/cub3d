#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		c_s1;

	c_s1 = ft_strlen(s1);
	res = malloc(c_s1 + 1);
	if (!res)
		return (0);
	while (*s1)
		*res++ = *s1++;
	*res = 0;
	return (res - c_s1);
}
