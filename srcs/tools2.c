#include "filler.h"

int			get_nearest(t_game *game, t_point *pos, t_point *ok, t_point *ref)
{
	////////// OVER ? 
	(void)game;
	if (((ok->x == 0 && ok->y == 0) || delta(pos, ref) <= delta(ok, ref))
	    && over(game, pos, E_EMPTY, 2) == TRUE)
		return (TRUE);
	return (FALSE);
}

int			farest_delta(t_game *game, t_point *pos, t_point *ok, t_point *ref)
{
	(void)game;
	if ((ok->x == 0 && ok->y == 0) || delta(pos, ref) <= delta(ok, ref))
		return (TRUE);
	return (FALSE);
}

int			get_better(t_game *game, t_point *ref,
				int (*f)(t_game *, t_point *, t_point *ok, t_point *ref))
{
	t_point pos;
	t_point ok;
	int		d;

	pos.x = 0;
	ft_bzero(&ok, sizeof(t_point));
	while (pos.x < game->board.size.x)
	{
		pos.y = 0;
		while (pos.y < game->board.size.y)
		{
			if (game->board.mx[pos.x][pos.y] == E_MINE
					|| game->board.mx[pos.x][pos.y] == E_LAST_MINE)
			{
				if (f(game, &pos, &ok, ref) == TRUE)
				{
					ok = pos;
					d = delta(&pos, ref);
				}
			}
			pos.y++;
		}
		pos.x++;
	}
	return (d);
}

t_point		nearest(t_game *game)
{
	t_point	pos;
	t_point ok;
	int		delta;

	ft_bzero(&ok, sizeof(t_point));
	delta = 0;
	pos.x = -1;
	while (++pos.x < game->board.size.x)
	{
		pos.y = -1;
		while (++pos.y < game->board.size.y)
		{
			if (game->board.mx[pos.x][pos.y] == E_ADV
					|| game->board.mx[pos.x][pos.y] == E_LAST_ADV)
			{
				if ((ok.x == 0 && ok.y == 0) ||
					get_better(game, &pos, get_nearest) <= delta)
				{
					ok = pos;
					delta = get_better(game, &pos, get_nearest);
				}
			}
		}
	}
	return (ok);
}
