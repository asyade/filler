#include "filler.h"
#include "fcntl.h"
#include <stdio.h>

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

static void	put_pos(int x, int y)
{
	ft_putnbr(x);
	ft_putchar(' ');
	ft_putnbr(y);
	ft_putchar('\n');
}

int	put_piece(t_filler *filler, t_list *lst, t_chunk **chunks)
{
	t_absis	*bs;
	t_list	*pos;
	t_list	*root;
	int	i;

	update_chunk(filler->map, chunks);
	i = -1;
	while (++i < NB_CHUNK)
	{
		root = lst;
		//printf("x%d y%d width%d height%d weight%d\n", chunks[i]->x, chunks[i]->y, chunks[i]->width, chunks[i]->height, chunks[i]->weight);
		while (lst)
		{
			bs = (t_absis *)lst->content;
			pos = get_positions(filler, bs->a[0], bs->a[1]);
			lst = lst->next;
			if (!pos)
				continue ;
			bs = (t_absis *)pos->content;
			if (!chunk_check_col(filler, chunks[i], bs->a[0], bs->b[1]))
				continue ;
			put_pos(bs->a[1], bs->a[0]);
			filler->piece->todo = 0;
			return (1);
		}
		lst = root;
	}
	return (0);
}

int	main(void)
{
	t_filler	*filler;
	t_list		*lst;
	t_list		*fptr;
	int			done;
	t_chunk			**chnks;
	filler = NULL;
	filler = ft_memalloc(sizeof(t_filler));
	chnks = NULL;
	while (fl_parse(&filler) > 0)
	{
		if (!filler->map || !filler->piece || !filler->piece->todo)
			continue ;
		if (!chnks && !(chnks = get_chunks(filler->map)))
			return (1);
		lst = get_all_abs(filler);
		done = put_piece(filler, lst, chnks);
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
