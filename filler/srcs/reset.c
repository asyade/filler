/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:21:20 by acorbeau          #+#    #+#             */
/*   Updated: 2017/07/17 18:21:48 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		reset_map(t_filler *fill, int height, int width)
{
	if (fill->map && fill->map->map)
	{
		while (fill->map->height--)
			free(fill->map->map[fill->map->height]);
	}
	ft_xclear(4);
	fill->map->map = ft_xcalloc(sizeof(char *) * height, 4);
	fill->map->height = height;
	fill->map->width = width;
}

int			reset_piece(t_filler *filler, int height, int width)
{
	if (filler->piece && filler->piece->data)
	{
		while (filler->piece->height--)
			free(filler->piece->data[filler->piece->height]);
	}
	ft_xclear(3);
	if (!(filler->piece->data = ft_xcalloc(sizeof(char *) * height, 3)))
		return (0);
	filler->piece->height = height;
	filler->piece->width = width;
	filler->piece->todo = 1;
	return (1);
}
