#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cpy_lst;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	cpy_lst = *lst;
	while (cpy_lst->next)
		cpy_lst = cpy_lst->next;
	cpy_lst->next = new;
}
