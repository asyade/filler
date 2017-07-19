/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cells.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:21:20 by acorbeau          #+#    #+#             */
/*   Updated: 2017/07/19 14:02:50 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int				cmp_dist(t_list *la, t_list *lb)
{
	int	a;
	int	b;

	a = ((t_absis *)la->content)->dist;
	b = ((t_absis *)lb->content)->dist;
	return (a < b) ? -1 : (a > b);
}

int				has_free_neigbors(t_filler *f, int x, int y)
{
	return (1);
	if (x - 1 >= 0 && x - 1 < f->map->width && y >= 0 &&
y < f->map->height && f->map->map[y][x - 1] == '.')
		return (1);
	if (x + 1 >= 0 && x + 1 < f->map->width && y >= 0 &&
y < f->map->height && f->map->map[y][x + 1] == '.')
		return (1);
	if (y - 1 >= 0 && y - 1 < f->map->height && x >= 0 &&
x < f->map->width && f->map->map[y - 1][x] == '.')
		return (1);
	if (y + 1 >= 0 && y + 1 < f->map->height && x >= 0 &&
x < f->map->width && f->map->map[y + 1][x] == '.')
		return (1);
	return (0);
}

void			get_min(t_chunk **chunks, int c)
{
	int		min;
	int		i;
	t_chunk	*tmp;

	min = LIMITS_INT_MAX;
	while (c--)
	{
		if (!(chunks[c]->weight < min))
			continue ;
		min = chunks[c]->weight;
		i = c;
	}
	tmp = chunks[0];
	chunks[0] = chunks[i];
	chunks[i] = tmp;
}
