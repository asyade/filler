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
	if (fill->map)
	{
		while (fill->map->height--)
		{
			free(fill->map->map[fill->map->height]);
		}
		free(fill->map->map);
	}
	else if (!(fill->map = ft_memalloc(sizeof(t_map))))
		return ;
	fill->map->map = ft_memalloc(sizeof(char *) * height);
	fill->map->height = height;
	fill->map->width = width;
}

int			reset_piece(t_filler *filler, int height, int width)
{
	if (filler->piece)
	{
		while (--filler->piece->height)
			free(filler->piece->data[filler->piece->height]);
		free(filler->piece->data);
	}
	else if (!(filler->piece = ft_memalloc(sizeof(t_piece))))
		return (0);
	if (!(filler->piece->data = ft_memalloc(sizeof(char *) * height)))
		return (0);
	filler->piece->height = height;
	filler->piece->width = width;
	filler->piece->todo = 1;
	return (1);
}
