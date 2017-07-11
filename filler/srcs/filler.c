#include "filler.h"
#include "fcntl.h"

int	main(int ac, char **av)
{
	t_filler	*filler;
	filler = NULL;
	while (fl_parse(&filler) > 0)
	{
		fl_log("Parse OK !");
		if (filler && filler->piece && filler->piece->todo)
			put_piece(filler);
	}
}
