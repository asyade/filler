#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include <fcntl.h>

# define LIMITS_INT_MAX 2147483647
# define LIMITS_INT_MIN -2147483648

# define NB_CHUNK 4

typedef struct		s_piece
{
	int				todo;
	int				height;
	int				width;
	char			**data;
}					t_piece;

typedef struct		s_absis
{
	int				a[2];
	int				b[2];
	int				dist;
}					t_absis;

typedef struct		s_map
{
	char			**map;
	int				width;
	int				height;
}					t_map;

typedef struct		s_filler
{
	int				nb;
	char			player;
	t_map			*map;
	t_piece			*piece;
}					t_filler;

typedef struct		s_chunk
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		weight;
}			t_chunk;

int		chunk_check_col(t_filler *filler, t_chunk *chunk, int x, int y);
void		update_chunk(t_map *map, t_chunk **chunks);
t_chunk		**get_chunks(t_map *map);

int					fl_parse(t_filler **filler);
void				fl_log(char *str);
t_list				*get_positions(t_filler *filler, int x, int y);
int					cmp_dist(t_list *la, t_list *lb);
void				scale_piece(t_piece *p);
int					has_free_neigbors(t_filler *f, int x, int y);
int					get_dist(int xa, int ya, int xb, int yb);
t_absis				*get_abs(t_filler *f, int x, int y);
t_list				*get_all_abs(t_filler *f);
void				reset_map(t_filler *fill, int height, int width);
int					reset_piece(t_filler *filler, int height, int width);

#endif
