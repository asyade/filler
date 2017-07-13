#include "libft.h"

t_list	*ft_lstpushsort(t_list **root, t_list *elem,
		int (*cmp)(t_list *, t_list *))
{
	t_list	*tmp;

	if (!(tmp = *root))
		return (*root = elem);
	if (cmp(tmp, elem) >= 0)
	{
		elem->next = tmp;
		return (*root = elem);
	}
	while (tmp->next)
	{
		if (cmp(tmp->next, elem) >= 0)
		{
			elem->next = tmp->next;
			return (tmp->next = elem);
		}
		tmp = tmp->next;
	}
	return (tmp->next = elem);
}
