/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:21:20 by acorbeau          #+#    #+#             */
/*   Updated: 2017/07/19 14:08:40 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdio.h>

static int	parse_player(t_filler **filler, char *line)
{
	if (!ft_strnequ(line, "$$$ exec p", 10))
		return (0);
	line += 10;
	if (*line != '1' && *line != '2')
		return (0);
	(*filler)->nb = (*line == '1') ? 1 : 2;
	(*filler)->player = (*line++ == '1') ? 'o' : 'x';
	if (!ft_strnequ(line, " : [", 4))
		return (-1);
	return (1);
}

void 		pre_map_pos(t_filler *filler)
{
	int		ecount;
	int		acount;
	int		x;
	int		y;
	char	tmp;

	y = -1;
	ecount = 0;
	acount = 0;
	if (!filler)
		return ;
	while (++y < filler->map->height)
	{
		x = -1;
		while (++x < filler->map->width)
		{
			tmp = filler->map->map[y][x];
			if (tmp == '.')
				continue ;
			if (ft_tolower(tmp) == filler->player)
				acount++;
			else
				ecount++;
		}
	}
	if (ecount)
		filler->map->allies = ft_xalloc(sizeof(long) * acount, 4);
	if (acount)
		filler->map->ennemies = ft_xalloc(sizeof(long) * ecount, 4);
	//printf("ennemies %d allies %d\n", ecount, acount);
}

void		get_map_pos(t_filler *f)
{
	int		x;
	int		y;
	char	tmp;
	int		ia;
	int		ie;

	y = -1;
	ia = 0;
	ie = 0;
	while (++y < f->map->height)
	{
		x = -1;
		while (++x < f->map->width)
		{
			tmp = f->map->map[y][x];
			if (tmp == '.')
				continue ;
			if (ft_tolower(tmp) == f->player)
				f->map->allies[ia++] = (PSET_X(0, x) | PSET_Y(0, y));
			else
				f->map->ennemies[ie++] = (PSET_X(0, x) | PSET_Y(0, y));
		}
	}
	f->map->acount = ia;
	f->map->ecount = ie;
}

static int	parse_map_cells(t_filler *filler)
{
	char	*line;
	int		i;

	filler->map->ennemies = NULL;
	filler->map->allies = NULL;
	line = NULL;
	if (get_next_line(0, &line) <= 0)
		return (0);
	i = -1;
	free(line);
	while (++i < filler->map->height)
	{
		if (get_next_line(0, &line) <= 0)
			return (0);
		filler->map->map[i] = ft_strdup(ft_strchr(line, ' ') + 1);
		free(line);
	}
	pre_map_pos(filler);
	get_map_pos(filler);
	return (1);
}

static int	parse_map(t_filler *filler, char *line)
{
	int	size[2];

	if (!line || !*line || !ft_strnequ(line, "Plateau ", 8))
		return (0);
	line += 8;
	if (!*line)
		return (0);
	size[0] = ft_atoi(line);
	line = ft_strchr(line, ' ');
	if (!line || !*line)
		return (0);
	size[1] = ft_atoi(line);
	reset_map(filler, size[0], size[1]);
	return (parse_map_cells(filler));
}

int			*new_xpoint(int x, int y, int map)
{
		int	*ret;

		ret = ft_xalloc(sizeof(int) * 2, map);
		ret[0] = x;
		ret[1] = y;
		return (ret);
}

void		parse_piece_node(t_piece *piece)//TODO derniére opti gérer le min comme le max ...
{
	t_list	*ret;
	int		y;
	int		x;

	ret = NULL;
	y = -1;
	piece->max[0] = 1;
	piece->max[1] = 1;
	while (++y < piece->height)
	{
		x = -1;
		while (++x < piece->width)
		{
			if (piece->data[y][x] == '.')
				continue ;
			ft_lstadd(&ret, ft_xlstcreate(new_xpoint(x, y, 3), sizeof(int) * 2, 3));
			piece->max[0] = X_MAX(x + 1, piece->max[0]);
			piece->max[1] = X_MAX(y + 1, piece->max[1]);
		}
	}
	piece->node = ret;
}

static int	parse_piece(t_filler *filler, char *line)
{
	int		size[2];
	char	*s;
	int		i;

	if (!line || !*line || !ft_strnequ(line, "Piece ", 6))
		return (0);
	line += 6;
	size[0] = ft_atoi(line);
	if (!(line = ft_strchr(line, ' ')) || !line || !*line)
		return (0);
	size[1] = ft_atoi(line);
	if (!reset_piece(filler, size[0], size[1]))
		return (0);
	s = NULL;
	i = -1;
	while (++i < size[0])
	{
		if (get_next_line(0, &s) <= 0)
			return (0);
		filler->piece->data[i] = s;
	}
	parse_piece_node(filler->piece);
	return (1);
}

int			fl_parse(t_filler **filler)
{
	int		len;
	char	*line;
	int		ret;

	ret = -1;
	line = NULL;
	if (!*filler)
		return (-1);
	if ((len = get_next_line(0, &line)) <= 0)
	{
		ft_strdel(&line);
		return (-1);
	}
	if (!(*filler)->nb)
		ret = (parse_player(filler, line)) ? 1 : -1;
	else if (ft_strnequ(line, "Plateau ", 8))
		ret = (parse_map(*filler, line)) ? 1 : -1;
	else if (ft_strnequ(line, "Piece ", 6))
		ret = (parse_piece(*filler, line)) ? 1 : -1;
	ft_strdel(&line);
	return (ret);
}
