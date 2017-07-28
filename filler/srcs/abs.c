/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:21:20 by acorbeau          #+#    #+#             */
/*   Updated: 2017/07/19 13:54:21 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static t_absis	*init_abs(int x, int y)
{
	t_absis	*ret;

	ret = ft_xalloc(sizeof(t_absis), 1);
	ret->a[0] = x;
	ret->a[1] = y;
	ret->dist = LIMITS_INT_MAX;
	return (ret);
}

/*t_absis			*get_abs(t_filler *f, int x, int y)
{
	t_absis	*ret;
	int		px;
	int		py;
	int		dst;

	py = -1;
	if (!(ret = init_abs(x, y)))
		return (NULL);
	while (++py < f->map->height)
	{
		px = -1;
		while (++px < f->map->width)
		{
			if (f->map->map[py][px] == '.' ||
ft_tolower(f->map->map[py][px]) == ft_tolower(f->player) ||
!has_free_neigbors(f, px, py) || ret->dist < (dst = get_dist(x, y, px, py)))
				continue ;
			ret->dist += dst;
			ret->b[0] = px;
			ret->b[1] = py;
		}
	}
	return (ret);
}*/

t_absis			*get_abs(t_filler *f, int x, int y)
{
	t_absis	*ret;
	int		i;
	int		px;
	int		py;
	int		dst;

	if (!(ret = init_abs(x, y)))
		return (NULL);
	i = -1;
	while (++i < f->map->ecount)
	{
		py = PGET_Y(f->map->ennemies[i]);
		px = PGET_X(f->map->ennemies[i]);
		if (!has_free_neigbors(f, px, py)
|| ret->dist < (dst = get_dist(x, y, px, py)))
			continue ;
		ret->dist += dst;
		ret->b[0] = px;
		ret->b[1] = py;
	}
	return (ret);
}

t_list			*get_all_abs(t_filler *f)
{
	int		i;
	int		tmp[2];
	t_list	*ret;
	t_list	*new;

	ret = NULL;
	i = -1;
	while (++i < f->map->acount)
	{
		tmp[0] = PGET_X(f->map->allies[i]);
		tmp[1] = PGET_Y(f->map->allies[i]);
		if (!has_free_neigbors(f, tmp[0], tmp[1]))
			continue ;
		new = ft_xlstcreate(get_abs(f, tmp[0], tmp[1]), sizeof(t_absis), 1);
		ft_lstpushsort(&ret, new, &cmp_dist);
	}
	return (ret);
}

/*t_list			*get_all_abs(t_filler *f)
{
	int		x;
	int		y;
	t_list	*ret;
	t_list	*new;

	ret = NULL;
	y = -1;
	while (++y < f->map->height)
	{
		x = -1;
		while (++x < f->map->width)
		{
			if (ft_tolower(f->map->map[y][x]) == f->player &&
has_free_neigbors(f, x, y))
			{
				new = ft_xlstcreate(get_abs(f, x, y), sizeof(t_absis), 1);
				ft_lstpushsort(&ret, new, &cmp_dist);
			}
		}
	}
	return (ret);
}*/
