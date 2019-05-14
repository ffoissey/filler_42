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
				if (game->to_play.x == 0 && game->to_play.y == 0)
				{
					game->to_play.x = start.x;
					game->to_play.y = start.y;
				}
				
				else if (game->mode == E_SPIDER_Y
					&& (game->board_size.x - start.x <= game->board_size.x - game->to_play.x
					|| start.x < game->to_play.x)
					&& get_delta(&start, &game->last_adv) <= get_delta(&game->to_play, &game->last_adv))
				{
					game->to_play.x = start.x;
					game->to_play.y = start.y;
				}
				else if (game->mode == E_SPIDER_X
					&& (game->board_size.y - start.y <= game->board_size.y - game->to_play.y
					|| start.y < game->to_play.y)
					&& get_delta(&start, &game->last_adv) <= get_delta(&game->to_play, &game->last_adv))
				{
					game->to_play.x = start.x;
					game->to_play.y = start.y;
				}
				else if (game->mode == E_ATTACK
					&& get_delta(&start, &game->last_adv) < get_delta(&game->to_play, &game->last_adv))
				{
					game->to_play.x = start.x;
					game->to_play.y = start.y;
				}
				else if (game->mode == E_CORE
					&& get_delta(&start, &game->core_adv) < get_delta(&game->to_play, &game->core_adv))
				{
					game->to_play.x = start.x;
					game->to_play.y = start.y;
				}
				else if (game->mode == E_EXPANSION
					&& get_delta(&start, &game->core_adv) > get_delta(&game->to_play, &game->core_adv))
				{
					game->to_play.x = start.x;
					game->to_play.y = start.y;
				}
				else if (game->mode == E_ANGLE
					&& (get_delta(&start, &game->angle) < get_delta(&game->to_play, &game->angle)
					|| (get_delta(&start, &game->angle) == get_delta(&game->to_play, &game->angle)
					&& get_delta(&start, &game->last_adv) < get_delta(&game->to_play, &game->last_adv))))
				{
					game->to_play.x = start.x;
					game->to_play.y = start.y;
				}
			}
			start.y++;
		}
		start.x++;
	}
}

static int		scanner(t_game *game, t_point *target, enum e_state state, int zone)
{
	int		x;
	int		max_x;
	int		y;
	int		max_y;

	x = target->x - zone < 0 ? 0 : target->x - zone;
	max_x = target->x + zone > game->board_size.x ? game->board_size.x : target->x + zone;
	max_y = target->y + zone > game->board_size.y ? game->board_size.y : target->y + zone;
	while (x < max_x)
	{
		y = target->y - zone < 0 ? 0 : target->y - zone;
		while (y < max_y)
		{
			if (game->board[x][y] == state)
				return (TRUE);
			y++;
		}
		x++;
	}
	return (FALSE);
}

void			ft_process(t_game *game)
{
	if (game->last_mine.x != 0 && game->last_mine.y != 0 && game->last_adv.x == 0 && game->last_adv.y == 0)
	{
		game->mode = E_EXPANSION; 
		ft_dprintf(2, "\033[32mExpansion\033[0m\n");
	}
	else if (get_delta(&game->last_mine, &game->angle) > get_delta(&game->last_mine, &game->last_adv)
			&& scanner(game, &game->angle, E_MINE, 3) == FALSE
			&& scanner(game, &game->last_adv, E_MINE, 5) == FALSE)
	{
		game->mode = E_ANGLE; 
		ft_dprintf(2, "\033[34mAngle\033[0m\n");
	}
	else if (get_delta(&game->last_mine, &game->core_adv) > get_delta(&game->last_mine, &game->last_adv)
			&& scanner(game, &game->last_adv, E_MINE, 5) == FALSE)
	{
		game->mode = E_CORE; 
		ft_dprintf(2, "\033[35mCore\033[0m\n");
	}
	else if (scanner(game, &game->last_adv, E_MINE, 3) == TRUE)
	{
		game->mode = E_ATTACK; 
		ft_dprintf(2, "\033[31mAttack\033[0m\n");
	}
	else if ((game->board_size.x - game->last_adv.x <= 10 && game->board_size.x - game->last_adv.x > 0)
		|| (game->last_adv.x > 0 && game->last_adv.x <= 10))
	{
		game->mode = E_SPIDER_Y; 
		ft_dprintf(2, "\033[36mSpider Y\033[0m\n");
	}
	else if ((game->board_size.y - game->last_adv.y <= 10 && game->board_size.y - game->last_adv.y > 0)
		|| (game->last_adv.y > 0 && game->last_adv.y <= 10))
	{
		game->mode = E_SPIDER_X; 
		ft_dprintf(2, "\033[33mSpider X\033[0m\n");
	}
	else
		ft_dprintf(2, "\033[34mAngle\033[0m\n");
	//ft_dprintf(2, "\033[34mLast_adv: x[%d] y[%d]\033[0m\n", game->last_adv.x, game->last_adv.y);
	find_potential(game);
	game->last_mine.x = game->contact.x;
	game->last_mine.y = game->contact.y;
	game->mode = E_ANGLE;
}


int	get_delta(t_point *a, t_point *b)
{
	return ((b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y));
}
