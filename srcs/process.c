#include "filler.h"

static unsigned char	pos_is_ok(t_game *game, t_point *pos,
							t_point *p, int *contact)
{
	if (pos->x + p->x < 0 || pos->y + p->y < 0
			|| pos->x + p->x >= game->board.size.x
			|| pos->y + p->y >= game->board.size.y)
	{
		if (game->piece.mx[p->x][p->y] == E_FULL)
			return (FALSE);
	}
	else if ((game->board.mx[pos->x + p->x][pos->y + p->y] == E_ADV
				|| game->board.mx[pos->x + p->x][pos->y + p->y] == E_LAST_ADV)
			&& game->piece.mx[p->x][p->y] == E_FULL)
		return (FALSE);
	else if (*contact > 1)
		return (FALSE);
	else if (((game->board.mx[pos->x + p->x][pos->y + p->y] == E_MINE)
			|| (game->board.mx[pos->x + p->x][pos->y + p->y] == E_LAST_MINE))
			&& game->piece.mx[p->x][p->y] == E_FULL)
	{
		game->contact.x = pos->x + p->x;
		game->contact.y = pos->y + p->y;
		(*contact)++;
	}
	return (TRUE);
}

static unsigned char	check_piece(t_game *game, t_point *pos)
{
	t_point	p;
	int		contact;

	contact = 0;
	p.x = 0;
	while (p.x < game->piece.size.x)
	{
		p.y = 0;
		while (p.y < game->piece.size.y)
		{
			if (pos_is_ok(game, pos, &p, &contact) == FALSE)
				return (FALSE);
			p.y++;
		}
		p.x++;
	}
	return (contact == 1);
}

static void				find_coord(t_game *game, t_strategy strategy)
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
			if (check_piece(game, &start) == TRUE)
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

void					ft_process(t_game *game)
{
	static	t_strategy	strategy[] = {angle_mode, attack_mode,
										spider_x_up_mode, spider_x_down_mode,
										spider_y_left_mode, spider_y_right_mode,
										core_mode, expansion_mode, conquest_mode, glue_mode};

	game->to_play.x = 0;
	game->to_play.y = 0;
	game->nearest_adv.x = 0;
	game->nearest_adv.y = 0;
	game->nearest_adv = nearest(game);
	if (game->nearest_adv.x < 0 || game->nearest_adv.y < 0)
	{
		game->nearest_adv.x = 0;
		game->nearest_adv.y = 0;
	}
	select_strategy(game);
	print_strategy(game);
	find_coord(game, strategy[game->mode]);
	game->last_mine.x = game->to_play.x;
	game->last_mine.y = game->to_play.y;
	game->last_adv.x = 0;
	game->last_adv.y = 0;
	game->turn++;
	if (scanner(game, &game->angle_target, E_MINE, 2) == TRUE
		|| scanner(game, &game->angle_target, E_ADV, 2) == TRUE
		|| scanner(game, &game->angle_target, E_EMPTY, 2) == FALSE)
		game->get_angle = 1;
	else if (game->turn * 2 > game->board.size.x
			|| game->turn * 2 > game->board.size.y)
		game->get_angle = 1;
	ft_dprintf(2, "ANGLE FREE: %s\n", game->get_angle == 0 ? "YES" : "NO");
}
