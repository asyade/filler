/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:21:20 by acorbeau          #+#    #+#             */
/*   Updated: 2017/07/19 13:54:21 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include <fcntl.h>

# define LIMITS_INT_MAX 2147483647
# define LIMITS_INT_MIN -2147483648

# define X_MAX(a, b) ((a > b) ? a : b)
# define X_MIN(a, b) ((a < b) ? a : b)

# define NB_CHUNK 4

# define XMAP_MAX 32
# define XMAP_SIZE 4094

# define PGET_X(i) ((int)((((long)i) & 0xffff0000) >> 16))
# define PGET_Y(i) ((int)(((long)i) & 0x0000ffff))

# define PSET_X(i, n) ((long)((i & 0x0000ffff) | (n << 16)))
# define PSET_Y(i, n) ((long)((((long)PGET_X(i)) << 16) | n))

# define XGET      0
# define XCREATE   1
# define XEXTENDE  2
# define XFREE	   3
# define XDEFRAG   4

# define XF_NONE     0
# define XF_OCCUPIED 1

typedef	struct		s_xmap
{
	void			**map;
	int				flags;
	size_t			ptr;
	size_t			size;
}					t_xmap;

typedef struct		s_piece
{
	int				todo;
	int				height;
	int				width;
	int				max[2];
	char			**data;
	t_list			*node;
}					t_piece;

typedef struct		s_absis
{
	int				a[2];
	int				b[2];
	int				dist;
	int				width[NB_CHUNK];
}					t_absis;

typedef struct		s_map
{
	char			**map;
	long			*ennemies;
	long			*allies;
	int				acount;
	int				ecount;
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
}					t_chunk;

void				*ft_xalloc(size_t size, int ref);
void				*ft_xcalloc(size_t size, int ref);
void				ft_xfree(void *ptr, int ref);
void				ft_xclear(int ref);
t_xmap				*ft_xmap(int ref, int mode);
t_list				*ft_xlstnew(void *content, size_t content_size, int ref);

void				free_filler(t_filler *filler);
void				get_min(t_chunk **chunks, int c);
void				chunk_update_abs_width(t_filler *f, t_chunk **ch, t_absis *ab);
int					chunk_check_col(t_filler *f, t_chunk *c, int x, int y);
void				update_chunk(t_map *map, t_chunk **chunks);
t_chunk				**get_chunks(t_map *map);

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
