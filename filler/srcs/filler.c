#include "filler.h"
#include "fcntl.h"
#include <stdio.h>

//TODO prendre la meilleur position par raport au dernier placement ennemie

void	free_filler(t_filler *filler)
{
	if (!filler)
		return ;
	if (filler->map)
	{
		while(--filler->map->height)
			free(filler->map->map[filler->map->height]);
		free(filler->map->map);
		free(filler->map);
	}
	if (filler->piece)
	{
		while (--filler->piece->height)
			free(filler->piece->data[filler->piece->height]);
		free(filler->piece->data);
		free(filler->piece);
	}
	free(filler);
}

int	main(int ac, char **av)
{
	t_filler	*filler;
	t_absis		*bs;
	t_list		*lst;
	filler = NULL;
	t_list		*pos;
	t_list		*fptr;
	char		msg[10000];
	int			turn;
	int			done;

	turn = 1;
	filler = ft_memalloc(sizeof(t_filler));
	while (fl_parse(&filler) > 0)
	{
		turn++;
		if (!filler->map || !filler->piece || !filler->piece->todo)
			continue ;
		lst = get_all_abs(filler);
		fptr = lst;
		done = 0;
		while (lst)
		{
			bs = (t_absis *)lst->content;
			pos = get_positions(filler, bs->a[0], bs->a[1]);
			lst = lst->next;
			if (!pos)
				continue ;
			bs = (t_absis *)pos->content;
			msg[0] = '\0';
			sprintf(msg, "%d %d\n", bs->a[1], bs->a[0]);
			ft_putstr(msg);
			filler->piece->todo = 0;
			done = 1;
			break ;
		}
		lst = fptr;
		while (lst)
		{
			fptr = lst;
			lst = lst->next;
			free(fptr->content);
			free(fptr);
		}
		if (!done)
			ft_putstr("0 0\n");
	}
	free_filler(filler);
}
