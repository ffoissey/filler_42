#include "filler.h"

void	speak(t_game *game, char **line)
{
	ft_strdel(line);
	free_matrix(&game->piece);
	ft_printf("%d %d\n", game->to_play.x, game->to_play.y);
	game->to_play.x = 0;
	game->to_play.y = 0;
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

int		get_delta(t_point *a, t_point *b)
{
	return ((b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y));
}

int		scanner(t_game *game, t_point *target, enum e_state state, int zone)
{
	int		x;
	int		max_x;
	int		y;
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
