#include "filler.h"

int		cmp_dist(t_list *la, t_list *lb)
{
	int	a;
	int	b;

	a = ((t_absis *)la->content)->dist;
	b = ((t_absis *)lb->content)->dist;
	return (a < b) ? -1 : (a > b);
}

int		has_free_neigbors(t_filler *f, int x, int y)
{
	if (x - 1 >= 0 && x - 1 < f->map->width && y >= 0 && y < f->map->height && f->map->map[y][x - 1] == '.')
		return (1);
	if (x + 1 >= 0 && x + 1 < f->map->width && y >= 0 && y < f->map->height && f->map->map[y][x + 1] == '.')
		return (1);
	if (y - 1 >= 0 && y - 1 < f->map->height && x >= 0 && x < f->map->width && f->map->map[y - 1][x] == '.')
		return (1);
	if (y + 1 >= 0 && y + 1 < f->map->height && x >= 0 && x < f->map->width && f->map->map[y + 1][x] == '.')
		return (1);
	return (0);
}

t_absis	*get_abs(t_filler *f, int x, int y)
{
	t_absis	*ret;
	int		px;
	int		py;
	int		dst;

	py = -1;
	if (!(ret = malloc(sizeof(t_absis))))
		return (NULL);
	ret->dist = LIMITS_INT_MAX;
	ret->a[0] = x;
	ret->a[1] = y;
	while (++py < f->map->height)
	{
		px = -1;
		while (++px < f->map->width)
		{
			if (f->map->map[py][px] == '.' || ft_tolower(f->map->map[py][px]) == ft_tolower(f->player))
				continue ;
			if (!has_free_neigbors(f, px, py))
				continue ;
			if (ret->dist < (dst = get_dist(x, y, px, py)))
				continue ;
			ret->dist = dst;
			ret->b[0] = px;
			ret->b[1] = py;
		}
	}
	return (ret);
}

t_list	*get_all_abs(t_filler *f)
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
		while(++x < f->map->width)
		{
			if (ft_tolower(f->map->map[y][x]) == f->player && has_free_neigbors(f, x, y))
			{
				new = ft_lstcreate(get_abs(f, x, y), sizeof(t_absis *));
				ft_lstpushsort(&ret, new, &cmp_dist);
			}
		}
	}
	return (ret);
}
