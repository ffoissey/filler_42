#include "filler.h"

int			over(t_game *game, t_point *target, enum e_state state, int zone)
{
	int		x;
	int		y;
	int		max_x;
	int		max_y;
	int		over;

	over = 0;
	x = target->x - zone < 0 ? 0 : target->x - zone;
	max_x = target->x + zone > game->board.size.x
			? game->board.size.x : target->x + zone;
	max_y = target->y + zone > game->board.size.y
			? game->board.size.y : target->y + zone;
	while (x < max_x)
	{
		y = target->y - zone < 0 ? 0 : target->y - zone;
		while (y < max_y)
		{
			if (game->board.mx[x][y] == state)
				over++;
			y++;
		}
		x++;
	}
	return (over > (zone * zone) / 2 + (zone * zone) / 3 ? TRUE : FALSE);
//	return (over > (zone * zone) / 2 + (zone * zone) / 4 ? TRUE : FALSE);
}

int			scanner(t_game *game, t_point *target, enum e_state state, int zone)
{
	int		x;
	int		y;
	int		max_x;
	int		max_y;

	x = target->x - zone < 0 ? 0 : target->x - zone;
	max_x = target->x + zone > game->board.size.x
			? game->board.size.x : target->x + zone;
	max_y = target->y + zone > game->board.size.y
			? game->board.size.y : target->y + zone;
	while (x < max_x)
	{
		y = target->y - zone < 0 ? 0 : target->y - zone;
		while (y < max_y)
		{
			if (game->board.mx[x][y] == state)
				return (TRUE);
			y++;
		}
		x++;
	}
	return (FALSE);
}

void		get_angle(t_game *game)
{
	game->angle_adv = choose_angle(game, &game->core_adv);
	game->angle_mine = choose_angle(game, &game->core_mine);
	game->angle_target.x = game->angle_mine.x == 0 ? game->board.size.x - 1 : 0;
	game->angle_target.y = game->angle_mine.y == 0 ? game->board.size.y - 1 : 0;
	game->angle_opmine.x = game->angle_target.x;
	game->angle_opmine.y = game->angle_target.y == 0
						? game->board.size.y - 1 : 0;
	game->angle_opadv.x = game->angle_target.x == 0
						? game->board.size.x - 1 : 0;
	game->angle_opadv.y = game->angle_target.y;
}

t_point		choose_angle(t_game *game, t_point *ref)
{
	t_point	win1;
	t_point	win2;
	t_point	p1;
	t_point	p2;
	t_point ret;

	ft_bzero(&p1, sizeof(t_point));
	p2.x = game->board.size.x - 1;
	p2.y = game->board.size.y - 1;
	win1 = (delta(ref, &p1) < delta(ref, &p2)) ? p1 : p2;
	p1.x = 0;
	p1.y = game->board.size.y - 1;
	p2.x = game->board.size.x - 1;
	p2.y = 0;
	win2 = (delta(ref, &p1) < delta(ref, &p2)) ? p1 : p2;
	ret = (delta(ref, &win1) < delta(ref, &win2)) ? win1 : win2;
	return (ret);
}

void		chose_better_angle(t_game *game)
{
	int	delta_mine;
	int	delta_adv;
	int	delta_target;

	if (game->board.size.x * game->board.size.y < 500)
	{
		delta_mine = get_better(game, &game->angle_opmine, farest_delta);
		delta_adv = get_better(game, &game->angle_opadv, farest_delta);
		delta_target = get_better(game, &game->angle_target, farest_delta);
		if (delta_mine > delta_adv && delta_mine > delta_target)
				game->better_angle = E_ANGLE_OPMINE;
		else if (delta_adv > delta_mine && delta_mine > delta_target)
				game->better_angle = E_ANGLE_OPADV;
		else
			game->better_angle = E_ANGLE_TARGET;
	}
	else
	{
		if (scanner(game, &game->angle_opmine, E_ADV, 3 == TRUE)
			|| scanner(game, &game->angle_opmine, E_MINE, 3 == TRUE))
			game->angle_opmine.x = game->board.size.x / 2;
		if (scanner(game, &game->angle_opadv, E_ADV, 3) == TRUE
			|| scanner(game, &game->angle_opadv, E_MINE, 3) == TRUE)
			game->angle_opadv.x = game->board.size.x / 2;
		if (scanner(game, &game->angle_target, E_ADV, 3) == TRUE
			|| scanner(game, &game->angle_target, E_MINE, 3) == TRUE)
			game->angle_target.y = game->board.size.y / 2;
		if (game->turn % 3 == 0)
			game->better_angle = E_ANGLE_TARGET;
		else if (game->turn % 3 == 1)
			game->better_angle = E_ANGLE_OPMINE;
		else
			game->better_angle = E_ANGLE_OPADV;
	}
}
