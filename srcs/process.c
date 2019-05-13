#include "filler.h"


void		print_debug(enum e_state **mx, t_point *size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < size->y)
	{
		j = 0;
		while (j < size->x)
		{
			if (mx[i][j] == E_EMPTY)
				ft_putchar('.');
			else if (mx[i][j] == E_FULL)
				ft_putchar('*');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}



//static enum e_state **make_piece_simple()


void	ft_process(t_game *game)
{
	//game->piece = make_piece_simple(game)
	print_debug(game->piece, &game->piece_size);
	(void)game;
}
