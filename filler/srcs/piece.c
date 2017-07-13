#include "filler.h"

/*
** Un example tragique de ce qui ce fais dans la branche algo
**/
void	scale_piece(t_piece *p)
{
	int	xmin;
	int	ymin;
	int	xmax;
	int	ymax;
	int	px;
	int	py;

	if (!p || !p->data)
		return ;
	py = -1;
	xmin = LIMITS_INT_MAX;
	ymin = LIMITS_INT_MAX;
	xmax = LIMITS_INT_MIN;
	ymax = LIMITS_INT_MIN;
	while (++py < p->height)
	{
		px = -1;
		while (++px < p->width - 1)
		{
			if (p->data[py][px] == '.')
				continue ;
			xmin = (xmin > px) ? px : xmin;
			ymin = (ymin > py) ? py : ymin;
			xmax = (xmax < px) ? px : xmax;
			ymax = (ymax < py) ? py : ymax;
		}
	}
	py = -1;
	while (++py < p->height)
	{
	//	p->data[py][xmax - xmin] = '\0';
		px = -1;
		while (++px < p->width - 1)
		{
			if (p->data[py][px] == '.')
				continue ;
			p->data[py][px] = '.';
			p->data[py][px - xmin] = '*';
			p->data[py][px] = '.';
			p->data[py - ymin][px] = '*';
		}
	}
	p->width -= xmin;
	p->height -= ymin;
}
