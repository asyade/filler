/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 18:21:53 by acorbeau          #+#    #+#             */
/*   Updated: 2017/07/17 18:21:58 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	fl_log(char *str)
{
	(void)str;
	return ;
	int	fd;

	if ((fd = open("debug.log", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR)) == -1)
		return ;
	ft_putendl_fd(str, fd);
	close(fd);
}
