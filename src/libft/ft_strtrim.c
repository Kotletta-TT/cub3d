#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = (int)ft_strlen(s1) - 1;
	while (j > i && ft_strchr(set, s1[j]))
		j--;
	len = (j - i) + 1;
	if (len > 0)
	{
		res = ft_substr(s1, i, len);
		return (res);
	}
	res = ft_calloc(1, 1);
	return (res);
}
