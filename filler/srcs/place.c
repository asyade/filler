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

int		can_put(t_filler *filler, int x, int y)
{
	int	i;
	int	j;
	int	col;

	col = 0;
	i = -1;
	while (++i < filler->piece->height)
	{
		j = -1;
		while (++j < filler->piece->width)
		{
			if (filler->piece->data[i][j] == '.')
				continue ;
			if (x + j >= filler->map->width ||
y + i >= filler->map->height || y + i < 0 || x + j < 0)
				return (0);
			if (is_player(filler, filler->map->map[i + y][j + x]) == 1)
				col++;
			else if (is_player(filler, filler->map->map[i + y][j + x]) == -1)
				return (0);
		}
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

	if (!(ret = instanciate_abs(x, y)))
		return (NULL);
	pcy = -1;
	while (++pcy < filler->piece->height)
	{
		pcx = -1;
		while (++pcx < filler->piece->width)
		{
			if (filler->piece->data[pcy][pcx] == '.')
				continue ;
			tmp = get_abs(filler, x + pcx, y + pcy);
			ret->dist += tmp->dist;
			ret->b[0] = tmp->b[0];
			ret->b[1] = tmp->b[1];
		}
	}
	return (ft_xlstcreate(ret, sizeof(t_absis *), 1));
}

t_list	*get_positions(t_filler *filler, int x, int y)
{
	int		px;
	int		py;
	t_list	*ret;

	ret = NULL;
	py = y - filler->piece->height;
	while ((py - y) < filler->piece->height * 2)
	{
		px = x - filler->piece->width;
		while ((px - x) < filler->piece->width * 2)
		{
			if (can_put(filler, px, py))
				ft_lstpushsort(&ret, get_pos_abs(filler, px, py),
&cmp_dist);
			px++;
		}
		py++;
	}
	return (ret);
}
