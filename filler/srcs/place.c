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
			if (is_player(filler, filler->map->map[i + y][j + x]) > 0)
				col++;
			else if (is_player(filler, filler->map->map[i + y][j + x]) < 0)
				return (0);
			else if (filler->map->map[i + y][j + x] != '.')
				return (0);
		}
	}
	return (col == 1);
}

void	put_piece(t_filler *filler)
{
	int	i;
	char	*fptr;

	i = -1;
	fl_log("Looking fors place ...");
	while (++i < filler->map->height)
	{
		if ((fptr = ft_strchr(filler->map->map[i], filler->player)) || (fptr = ft_strchr(filler->map->map[i], ft_toupper(filler->player))))
		{
			fl_log("Put piece ...");
			printf("%d %d\n", (int)(fptr - ft_strlen(filler->map->map[i])), i);//todo replace with ft_printf
			return ;
		}
	}
}
