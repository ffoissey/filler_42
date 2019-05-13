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

unsigned char	check_piece(t_game *game, int pos_y, int pos_x)
{
	int		i;
	int		j;
	int		contact;

	contact = 0;
	i = 0;
	while (i < game->piece_size.y)
	{
		j = 0;
		while (j < game->piece_size.x)
		{
			if (pos_y + i < 0 || pos_x + j < 0
				|| pos_y + i >= game->board_size.y
				|| pos_x + j >= game->board_size.x)
			{
				if (game->piece[i][j] == E_FULL)
					return (FALSE);
			}
			else if ((game->board[pos_y + i][pos_x + j] == E_ADV
					|| game->board[pos_y + i][pos_x + j] == E_LAST_ADV)
					&& game->piece[i][j] == E_FULL)
				return (FALSE);
			else if (contact > 1)
				return (FALSE);
			else if (((game->board[pos_y + i][pos_x + j] == E_MINE)
					|| (game->board[pos_y + i][pos_x + j] == E_LAST_MINE))
					&& game->piece[i][j] == E_FULL)
			{
				game->contact.y = pos_y + i;
				game->contact.x = pos_x + j;
				contact++;
			}
			j++;
		}
		i++;
	}
	return (contact == 1);
}


void			find_potential(t_game *game)
{
	t_point end;
	t_point	start;

	start.y = 0 - game->piece_size.y + 1;
	end.y = game->board_size.y + game->piece_size.y - 1;
	end.x = game->board_size.x + game->piece_size.x - 1;
	while (start.y < end.y)
	{
		start.x = 0 - game->board_size.x + 1;
		while (start.x < end.x)
		{
			if (check_piece(game, start.y, start.x) == TRUE)
			{
				
				if (game->to_play.x == -1
					|| get_delta(&start, &game->core_adv) < get_delta(&game->to_play, &game->core_adv))
				{
					game->to_play.x = start.x;
					game->to_play.y = start.y;
				}
			//	ft_printf("Potential: \033[32mx[%d] y[%d]\033[0m\n", start.y, start.x);
			}
			start.x++;
		}
		start.y++;
	}
}

void			ft_process(t_game *game)
{
//	ft_printf("\nBOARD : mine: %c, adv: %c\n", game->my_char, game->adv_char);
//	print_debug(game->board, &game->board_size, game);
//	ft_printf("\nPIECE : \n");
//	print_debug(game->piece, &game->piece_size, game);
	find_potential(game);
//	ft_printf("\n\n");
}
