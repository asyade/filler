/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:21:20 by acorbeau          #+#    #+#             */
/*   Updated: 2017/07/17 18:21:48 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	parse_player(t_filler **filler, char *line)
{
	fl_log(line);
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

static int	parse_map_cells(t_filler *filler)
{
	char	*line;
	int	i;

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



static int	parse_piece(t_filler *filler, char *line)
{
	int	size[2];
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
	return (1);
}

int		fl_parse(t_filler **filler)
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
		free(*filler);
		*filler = NULL;
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
