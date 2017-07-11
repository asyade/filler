#include "filler.h"

#include "stdio.h"

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
