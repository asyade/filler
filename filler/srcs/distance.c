/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 04:13:35 by acorbeau          #+#    #+#             */
/*   Updated: 2017/07/12 04:43:38 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		get_dist(int xa, int ya, int xb, int yb)
{
	int	pa;
	int	pb;

	pa = ft_pow(xb - xa, 2);
	pb = ft_pow(yb - ya, 2);
	return (ft_sqrt(pa + pb));
}


