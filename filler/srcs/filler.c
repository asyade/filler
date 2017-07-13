#include "filler.h"
#include "fcntl.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_filler	*filler;
	t_absis		*bs;
	t_list		*lst;
	filler = NULL;
	t_list		*pos;
	char		msg[10000];
	int			turn;

	turn = 1;
	while (fl_parse(&filler) > 0)
	{
		turn++;
		if (!filler || !filler->map || !filler->piece || !filler->piece->todo)
			continue ;
		lst = get_all_abs(filler);
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
			break ;
		}
	}
}
