#include "filler.h"

void		print_debug(enum e_state **mx, t_point *start, t_point *size)
{
	int	i;
	int	j;

	i = start->y;
	ft_printf("size_x: %d, size_y: %d\n", size->x, size->y);
	while (i < size->y)
	{
		j = start->x;
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
/*
static void		make_piece_simple(t_game *game)
{
	int		y;
	int		x;
	int		tmp_x;
	int		max_y;
	int		max_y;
	int		reduce;


	y = game->piece_start_size.y;
	max_y = game->piece_size.y;
	x = game->piece_start_size.x;
	tmp_x = x;
	max_x = game->piece_size.x;
	while (y < max_y)
	{
		x = tmp_x;
		reduce = 0;
		while (x < max.y)
		{
			if (game->piece[x] == E_FULL)
		}
	}
}
*/

void			ft_process(t_game *game)
{
	ft_printf("FIRST : \n");
	print_debug(game->piece, &game->piece_start_size, &game->piece_size);
//	make_piece_simple(game);
	ft_printf("\nSECOND : \n");
	print_debug(game->piece, &game->piece_start_size, &game->piece_size);
	ft_printf("\n\n");
	(void)game;
}
