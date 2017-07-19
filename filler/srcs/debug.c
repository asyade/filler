/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:21:53 by acorbeau          #+#    #+#             */
/*   Updated: 2017/07/19 14:06:54 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	fl_log(char *str)
{
	(void)str;
	return ;
}

void	free_filler(t_filler *filler)
{
	if (!filler)
		return ;
	if (filler->map)
	{
		while (--filler->map->height)
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
