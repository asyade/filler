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
	fl_log("Player parsed");
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
	fl_log("Parsing map...");
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

int		reset_piece(t_filler *filler, int height, int width)
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

void		debug_piece(t_piece *piece)
{
	int	i;
	if (!piece)
		return ;
	i = 0;
	while (i < piece->height)
	{
		fl_log(piece->data[i++]);
	}
}

static int	parse_piece(t_filler *filler, char *line)
{
	int	size[2];
	char	*s;
	int		i;

	fl_log("Parsing piece...");
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
	fl_log("Piece parsed !");
	debug_piece(filler->piece);
	return (1);
}

int		fl_parse(t_filler **filler)
{
	int		len;
	char	*line;
	int		ret;

	ret = -1;
	line = NULL;
	if (!*filler && !(*filler = ft_memalloc(sizeof(t_filler))))
		return (-1);
	if ((len = get_next_line(0, &line)) <= 0)
	{
		free(*filler);
		*filler = NULL;
		return (-1);
	}
	if (!(*filler)->nb)
	{
		if (parse_player(filler, line))
			ret = 1;
		else
			ret = -1;
	}
	else if (ft_strnequ(line, "Plateau ", 8))
	{
		if (parse_map(*filler, line))
			ret = 1;
		else
			ret = -1;
	}
	else if (ft_strnequ(line, "Piece ", 6))
	{
		if (parse_piece(*filler, line))
			ret = 1;
		else
			ret = -1;
	}
	ft_strdel(&line);
	return (ret);
}
