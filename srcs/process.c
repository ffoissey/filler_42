#include "filler.h"

void		print_debug(enum e_state **mx, t_point *size, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	ft_printf("size_x: %d, size_y: %d\n", size->y, size->x);
	while (i < size->y)
	{
		j = 0;
		while (j < size->x)
		{
			if (mx[i][j] == E_FULL)
				ft_putchar('*');
			else if (mx[i][j] == E_ADV)
				ft_putchar(game->adv_char);
			else if (mx[i][j] == E_LAST_ADV)
				ft_putchar(game->adv_last_char);
			else if (mx[i][j] == E_MINE)
				ft_putchar(game->my_char);
			else if (mx[i][j] == E_LAST_MINE)
				ft_putchar(game->my_last_char);
			else if (mx[i][j] == E_EMPTY)
				ft_putchar('.');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
}

unsigned char	check_piece(t_game *game, int pos_x, int pos_y)
{
	int		x;
	int		y;
	int		contact;

	contact = 0;
	x = 0;
	while (x < game->piece_size.x)
	{
		y = 0;
		while (y < game->piece_size.y)
		{
			if (pos_x + x < 0 || pos_y + y < 0
				|| pos_x + x >= game->board_size.x
				|| pos_y + y >= game->board_size.y)
			{
				if (game->piece[x][y] == E_FULL)
					return (FALSE);
			}
			else if ((game->board[pos_x + x][pos_y + y] == E_ADV
					|| game->board[pos_x + x][pos_y + y] == E_LAST_ADV)
					&& game->piece[x][y] == E_FULL)
				return (FALSE);
			else if (contact > 1)
				return (FALSE);
			else if (((game->board[pos_x + x][pos_y + y] == E_MINE)
					|| (game->board[pos_x + x][pos_y + y] == E_LAST_MINE))
					&& game->piece[x][y] == E_FULL)
			{
				game->contact.x = pos_x + x;
				game->contact.y = pos_y + y;
				contact++;
			}
			y++;
		}
		x++;
	}
	return (contact == 1);
}


void			find_potential(t_game *game)
{
	t_point end;
	t_point	start;

	start.x = 0 - game->piece_size.x;
	end.x = game->board_size.x + game->piece_size.x;
	end.y = game->board_size.y + game->piece_size.y;
	while (start.x < end.x)
	{
		start.y = 0 - game->piece_size.y;
		while (start.y < end.y)
		{
			if (check_piece(game, start.x, start.y) == TRUE)
			{
				if (game->to_play.x == -1
					|| get_delta(&start, &game->core_adv) < get_delta(&game->to_play, &game->core_adv))
				{
					game->to_play.x = start.x;
					game->to_play.y = start.y;
				}
			//	ft_dprintf(2, "Potential: \033[32mx[%d] y[%d]\033[0m\n", start.x, start.y);
			}
			start.y++;
		}
		start.x++;
	}
}

void			ft_process(t_game *game)
{
//	ft_dprintf(2, "GAME ACTION: %s\n", "process");
//	ft_printf("\nBOARD : mine: %c, adv: %c\n", game->my_char, game->adv_char);
//	print_debug(game->board, &game->board_size, game);
//	ft_printf("\nPIECE : \n");
//	print_debug(game->piece, &game->piece_size, game);
	find_potential(game);
//	ft_printf("\n\n");
}


int	get_delta(t_point *a, t_point *b)
{
	return ((b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y));
}
