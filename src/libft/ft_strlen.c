#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;
	char	*new_s;

	i = 0;
	new_s = (char *) s;
	while (new_s[i])
		i++;
	return (i);
}
