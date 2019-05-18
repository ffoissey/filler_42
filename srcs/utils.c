#include "filler.h"

void	speak(t_game *game, char **line)
{
	ft_strdel(line);
	free_matrix(&game->piece);
	ft_printf("%d %d\n", game->to_play.x, game->to_play.y);
	game->action = E_GET_BOARD_SIZE;
}

void	error(t_game *game, char **line)
{
	ft_strdel(line);
	free_matrix(&game->piece);
	free_matrix(&game->board);
	game->action = E_ERROR;
	ft_putendl_fd("Error", 2);
}

void	free_matrix(t_mx *mx)
{
	int		x;

	x = 0;
	while (x < mx->size.x)
	{
		free(mx->mx[x]);
		mx->mx[x] = NULL;
		x++;
	}
	free(mx->mx);
	mx->mx = NULL;
	mx->size.x = 0;
	mx->size.y = 0;
}

static int	get_better(t_game *game, t_point *ref)
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
				//// OVER IS GOOD ?
				if ((ok.x == 0 && ok.y == 0)
					|| (delta(&pos, ref) <= delta(&ok, ref)
					&& over(game, &pos, E_EMPTY, 2) == TRUE))
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

t_point	nearest(t_game *game)
{
	t_point	pos;
	t_point ok;
	int	 	delta;
	int		tmp_delta;

	ft_bzero(&ok, sizeof(t_point));
	delta = 0;
	pos.x = 0;
	while (pos.x < game->board.size.x)
	{
		pos.y = 0;
		while (pos.y < game->board.size.y)
		{
			if (game->board.mx[pos.x][pos.y] == E_ADV
					|| game->board.mx[pos.x][pos.y] == E_LAST_ADV)
			{
				tmp_delta = get_better(game, &pos);
				if ((ok.x == 0 && ok.y == 0) || tmp_delta <= delta)
				{
					ok = pos;
					delta = tmp_delta;
				}
				tmp_delta = delta + 1;
			}
			pos.y++;
		}
		pos.x++;
	}
	return (ok);
}

int		farest_delta(t_game *game, t_point *point)
{
	t_point	pos;
	t_point	better;
	int		d;

	d = -1;
	pos.x = 0;
	while (pos.x < game->board.size.x)
	{
		pos.y = 0;
		while (pos.y < game->board.size.y)
		{
			if (game->board.mx[pos.x][pos.y] == E_MINE
					|| game->board.mx[pos.x][pos.y] == E_LAST_ADV)
			{
				if (d == -1 || delta(point, &pos) < delta(point, &better))
				{
					better = pos;
					d = delta(point, &pos);
				}
			}
			pos.y++;
		}
		pos.x++;
	}
	return (d);
}
