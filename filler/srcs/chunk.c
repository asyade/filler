/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 14:03:01 by acorbeau          #+#    #+#             */
/*   Updated: 2017/07/19 14:05:44 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static t_chunk	*alloc_chunk(int x, int y, int width, int height)
{
	t_chunk	*ret;

	if (!(ret = malloc(sizeof(t_chunk))))
		return (NULL);
	ret->x = x;
	ret->y = y;
	ret->width = width;
	ret->height = height;
	return (ret);
}

void			chunk_iter(t_map *map, t_chunk *chunk)
{
	int	x;
	int	y;

	chunk->weight = 0;
	y = chunk->y - 1;
	while (++y < chunk->height + chunk->y)
	{
		x = chunk->x - 1;
		while (++x < chunk->width + chunk->x)
		{
			if (map->map[y][x] != '.')
				chunk->weight++;
		}
	}
}

void			update_chunk(t_map *map, t_chunk **chunks)
{
	int	i;

	i = -1;
	while (++i < NB_CHUNK)
		chunk_iter(map, chunks[i]);
	i = -1;
	while (++i < NB_CHUNK)
	{
		get_min(chunks + i, NB_CHUNK - i);
	}
	i = -1;
}

int				chunk_check_col(t_filler *filler, t_chunk *chunk, int x, int y)
{
	int	px;
	int	py;
	int	ret;

	ret = 0;
	py = y - 1;
	while (++py - y < filler->piece->height)
	{
		px = x - 1;
		while (++px - x < filler->piece->width)
		{
			if (filler->piece->data[py - y][px - x] == '.')
				continue ;
			if (px - chunk->x >= 0 && py - chunk->y >= 0 &&
px <= chunk->width + chunk->x && py <= chunk->height + chunk->y)
				ret++;
		}
	}
	return (ret);
}

t_chunk			**get_chunks(t_map *map)
{
	t_chunk	**chunks;
	int		width;
	int		height;

	width = (map->width % 2) ? (map->width / 2) + 1 : map->width / 2;
	height = (map->height % 2) ? (map->height / 2) + 1 : map->height / 2;
	if (!(chunks = (t_chunk **)malloc(sizeof(t_chunk *) * 4)))
		return (NULL);
	if (!(chunks[0] = alloc_chunk(0, 0, width, height)))
		return (NULL);
	if (!(chunks[1] = alloc_chunk(0, height, width, (map->height % 2) ?
					height - 1 : height)))
		return (NULL);
	if (!(chunks[2] = alloc_chunk(width, 0, (map->width % 2) ?
					width - 1 : width, height)))
		return (NULL);
	if (!(chunks[3] = alloc_chunk(width, height, (map->width % 2) ?
width - 1 : width, (map->height % 2) ? height - 1 : height)))
		return (NULL);
	return (chunks);
}
