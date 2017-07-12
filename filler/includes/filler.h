#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include <fcntl.h>

typedef struct		s_piece
{
	int		todo;
	int		height;
	int		width;
	char		**data;
}			t_piece;

typedef struct		t_absis
{
	int				a[2];
	int				b[2];
	int				dist;
}

typedef struct		s_map
{
	char		**map;
	int		width;
	int		height;
}			t_map;

typedef struct		s_filler
{
	int		nb;
	char		player;
	t_map		*map;
	t_piece		*piece;
}			t_filler;

int			fl_parse(t_filler **filler);
void			fl_log(char *str);
void			put_piece(t_filler *filler);
int				get_dist(int xa, int ya, int xb, int yb);

#endif
