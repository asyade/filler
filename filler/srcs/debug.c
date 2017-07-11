#include "filler.h"

void	fl_log(char *str)
{
	int	fd;

	if ((fd = open("debug.log", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR)) == -1)
		return ;
	ft_putendl_fd(str, fd);
	close(fd);
}
