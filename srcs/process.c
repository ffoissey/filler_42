#include "filler.h"

unsigned char	check_piece(t_game *game, int pos_x, int pos_y)
{
	int		x;
	int		y;
	int		contact;

	contact = 0;
	x = 0;
	while (x < game->piece.size.x)
	{
		y = 0;
		while (y < game->piece.size.y)
		{
			if (pos_x + x < 0 || pos_y + y < 0
				|| pos_x + x >= game->board.size.x
				|| pos_y + y >= game->board.size.y)
			{
				if (game->piece.mx[x][y] == E_FULL)
					return (FALSE);
			}
			else if ((game->board.mx[pos_x + x][pos_y + y] == E_ADV
					|| game->board.mx[pos_x + x][pos_y + y] == E_LAST_ADV)
					&& game->piece.mx[x][y] == E_FULL)
				return (FALSE);
			else if (contact > 1)
				return (FALSE);
			else if (((game->board.mx[pos_x + x][pos_y + y] == E_MINE)
					|| (game->board.mx[pos_x + x][pos_y + y] == E_LAST_MINE))
					&& game->piece.mx[x][y] == E_FULL)
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


void			find_potential(t_game *game, t_strategy strategy)
{
	t_point end;
	t_point	start;
	int		tmp_y;

	start.x = 0 - game->piece.size.x;
	tmp_y = 0 - game->piece.size.y;
	end.x = game->board.size.x + game->piece.size.x;
	end.y = game->board.size.y + game->piece.size.y;
	while (start.x < end.x)
	{
		start.y = tmp_y;
		while (start.y < end.y)
		{
			if (check_piece(game, start.x, start.y) == TRUE)
			{
				if (game->to_play.x == 0 && game->to_play.y == 0)
					game->to_play = start;
				else if (strategy(game, &start) == TRUE)
					game->to_play = start;
			}
			start.y++;
		}
		start.x++;
	}
}

void			ft_process(t_game *game)
{
	static	t_strategy	strategy[] = {angle_mode, attack_mode,
									spider_x_mode, spider_y_mode,
									core_mode, expansion_mode};

	select_strategy(game);
	find_potential(game, strategy[game->mode]);
	game->last_mine.x = game->contact.x;
	game->last_mine.y = game->contact.y;
	game->mode = E_ANGLE;
}
