/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 04:13:35 by acorbeau          #+#    #+#             */
/*   Updated: 2017/07/19 14:01:35 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	get_dist(int x1, int y1, int x2, int y2)
{
	int	distance;
	int	distancex;
	int	distancey;

	distancex = (x2 - x1) * (x2 - x1);
	distancey = (y2 - y1) * (y2 - y1);
	distance = distancex + distancey;
	return ((int)distance);
}
