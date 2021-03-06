/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:21:53 by acorbeau          #+#    #+#             */
/*   Updated: 2017/07/19 14:06:54 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "fcntl.h"
#include <stdio.h>

static void	put_pos(int x, int y)
{
	ft_putnbr(x);
	ft_putchar(' ');
	ft_putnbr(y);
	ft_putchar('\n');
}

void		lst_insert_nodoub(t_list **lst, t_list *elem)
{
	t_list	*tmp;
	t_absis	*a;
	t_absis	*b;

	b = (t_absis *)elem->content;
	tmp = *lst;
	while (tmp)
	{
		a = (t_absis *)tmp->content;
		if (a->a[0] == b->a[0] && a->a[1] == b->a[1])
			return ;
		tmp = tmp->next;
	}
	ft_lstaddfront(lst, elem);
}

int			choose_piece(t_filler *filler, t_list *place, t_chunk **chunks)
{
	t_absis	*ab;

	(void)chunks;
	if (!place)
		return (0);
	ab = (t_absis *)place->content;
	put_pos(ab->a[1], ab->a[0]);
	filler->piece->todo = 0;
	return (1);
}

int			put_piece(t_filler *filler, t_list *lst, t_chunk **chunks)
{
	t_absis	*bs;
	t_list	*pos;
	t_list	*avaible;

	avaible = NULL;
	while (lst)
	{
		bs = (t_absis *)lst->content;
		pos = get_positions(filler, bs->a[0], bs->a[1]);
		lst = lst->next;
		if (!pos)
			continue ;
		bs = (t_absis *)pos->content;
		lst_insert_nodoub(&avaible, ft_xlstcreate(bs, sizeof(t_absis), 1));
	}
	return (choose_piece(filler, avaible, chunks));
}

int			main(void)
{
	t_filler		*filler;
	t_list			*lst;
	int				done;
	t_chunk			**chnks;

	filler = NULL;
	filler = ft_xcalloc(sizeof(t_filler), 2);
	filler->map = ft_xcalloc(sizeof(t_map), 2);
	filler->piece = ft_xcalloc(sizeof(t_piece), 2);
	chnks = NULL;
	while (fl_parse(&filler) > 0)
	{
		if (!filler->map || !filler->piece || !filler->piece->todo)
			continue ;
		lst = get_all_abs(filler);
		done = put_piece(filler, lst, chnks);
		if (!done)
			ft_putstr("0 0\n");
		ft_xclear(1);
	}
	ft_xclear(2);
}
