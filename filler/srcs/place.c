#include "filler.h"

#include "stdio.h"

int	is_player(t_filler *filler, char c)
{
	c = ft_tolower(c);
	if (c == filler->player)
		return (1);
	if (c == '.')
		return (0);
	return (-1);
}

int	can_put(t_filler *filler, int x, int y)
{
	int	i;
	int	j;
	int	col;


	if (x < 0 || y < 0 || x + filler->piece->width > filler->map->width || y + filler->piece->height > filler->map->height)
		return (0);
	col = 0;
	i = -1;
	while (++i < filler->piece->height)
	{
		j = -1;
		while (++j < filler->piece->width)
		{
			if (filler->piece->data[i][j] == '.')
				continue ;
			if (is_player(filler, filler->map->map[i + y][j + x]) == 1)
				col++;
			else if (is_player(filler, filler->map->map[i + y][j + x]) == -1 || col > 1)
				return (0);
		}
	}
	return (col == 1 ? 1 : 0);
}


t_list	*get_pos_abs(t_filler *filler, int x, int y)
{
	t_absis	*ret;
	t_absis	*tmp;
	int		pcx;
	int		pcy;

	if (!(ret = malloc(sizeof(t_absis))))
		return (NULL);
	ret->a[0] = x;
	ret->a[1] = y;
	ret->dist = LIMITS_INT_MAX;
	pcy = -1;
	while (++pcy < filler->piece->height)
	{
		pcx = -1;
		while (++pcx < filler->piece->width)
		{

			if (filler->piece->data[pcy][pcx] == '.')
				continue ;
			tmp = get_abs(filler, x + pcx, y + pcy);
			if (tmp->dist > ret->dist)
				continue ;
			ret->dist = tmp->dist;
			ret->b[0] = tmp->b[0];
			ret->b[1] = tmp->b[1];
			free(tmp);
		}
	}
	return (ft_lstcreate(ret, sizeof(t_absis *)));
}

t_list	*get_positions(t_filler *filler, int x, int y)
{
	int		px;
	int		py;
	t_list	*ret;

	ret = NULL;
	py = (y + 1) - filler->piece->height;
	while ((py - y) < filler->piece->height * 2)
	{
		px = x - filler->piece->width + 1;
		while ((px - x) < filler->piece->width * 2)
		{
			if (!(px < 0 || py < 0 ||
				px + filler->piece->width > filler->map->width ||
				py + filler->piece->height > filler->map->height) &&
				can_put(filler, px, py))
					ft_lstpushsort(&ret, get_pos_abs(filler, px, py), &cmp_dist);
			px++;
		}
		py++;
	}
	return (ret);
}
