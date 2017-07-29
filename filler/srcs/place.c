/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:22:15 by acorbeau          #+#    #+#             */
/*   Updated: 2017/07/19 14:57:20 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		is_player(t_filler *filler, char c)
{
	c = ft_tolower(c);
	if (c == filler->player)
		return (1);
	if (c == '.')
		return (0);
	return (-1);
}

int		is_inside_map(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (0);
	return (1);
}

int		can_put(t_filler *filler, int x, int y)
{
	t_list	*lst;
	int		*n;
	int		col;
	int		i;

	col = 0;
	lst = filler->piece->node;
	while (lst)
	{
		n = (int *)lst->content;
		lst = lst->next;
		if (!is_inside_map(filler->map, n[0] + x, n[1] + y))
			return (0);
		i = is_player(filler, filler->map->map[n[1] + y][n[0] + x]);
		if (i == 1)
			col++;
		else if (i == -1)
			return (0);
	}
	return (col == 1 ? 1 : 0);
}

t_absis	*instanciate_abs(int x, int y)
{
	t_absis	*ret;

	if (!(ret = ft_xalloc(sizeof(t_absis), 1)))
		return (NULL);
	ret->a[0] = x;
	ret->a[1] = y;
	ret->dist = LIMITS_INT_MAX;
	return (ret);
}

t_list	*get_pos_abs(t_filler *filler, int x, int y)
{
	t_absis	*ret;
	t_absis	*tmp;
	int		pcx;
	int		pcy;
	t_list	*lst;

	if (!(ret = instanciate_abs(x, y)))
		return (NULL);
	lst = filler->piece->node;
	while (lst)
	{
		pcx = *((int *)lst->content);
		pcy = *((int *)(lst->content + 1));
		tmp = get_abs(filler, x + pcx, y + pcy);
		ret->dist += tmp->dist;
		ret->b[0] = tmp->b[0];
		ret->b[1] = tmp->b[1];
		lst = lst->next;
	}
	return (ft_xlstcreate(ret, sizeof(t_absis *), 1));
}
t_list	*get_positions(t_filler *filler, int x, int y)
{
	int		px;
	int		py;
	t_list	*ret;

	ret = NULL;
	py = y - filler->piece->max[1];
	while ((py - y) + filler->piece->min[1] < 1)
	{
		px = x - filler->piece->max[0];
		while ((px - x) + filler->piece->min[0] < 1)
		{
			if (can_put(filler, px, py))
				ft_lstpushsort(&ret, get_pos_abs(filler, px, py), &cmp_dist);
			px++;
		}
		py++;
	}
	return (ret);
}
