#include "filler.h"

int		delta(t_point *a, t_point *b)
{
	return ((b->x - a->x)) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y);
}

int		over(t_game *game, t_point *target, enum e_state state, int zone)
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
//	return (over > (int)((zone * zone) * percent) ? TRUE : FALSE);
	return (over > (zone * zone) / 2 + (zone * zone) / 3 ? TRUE : FALSE);
//	return (over > (zone * zone) / 2 ? TRUE : FALSE);
}

int		scanner(t_game *game, t_point *target, enum e_state state, int zone)
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
