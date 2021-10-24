#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	if (!s)
		return (0);
	if (ft_strlen(s) > start)
	{
		i = 0;
		res = malloc(len + 1);
		if (!res)
			return (0);
		while (i < len)
		{
			res[i] = s[i + start];
			i++;
		}
		res[i] = 0;
		return (res);
	}
	res = ft_calloc(1, 1);
	if (!res)
		return (0);
	return (res);
}
