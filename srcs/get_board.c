#include "filler.h"

unsigned char			check_first_line_board(unsigned int row, char *line)
{
	size_t	i;
	size_t	max;
	size_t	count;

	i = 0;
	max = row + 4;
	if (ft_strlen(line) != max)
		return (FALSE);
	while (i < 4)
	{
		if (line[i] != ' ')
			return (FALSE);
		i++;
	}
	count = 0;
	while (i < max)
	{
		if (count % 10 + '0' != line[i])
			return (FALSE);
		count++;
		i++;
	}
	return (TRUE);
}

t_point					choose_angle(t_game *game, t_point *ref)
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

static void				get_angle(t_game *game)
{
	game->angle_adv = choose_angle(game, &game->core_adv);
	game->angle_mine = choose_angle(game, &game->core_mine);
	game->angle_target.x = game->angle_mine.x == 0 ? game->board.size.x - 1 : 0;
	game->angle_target.y = game->angle_mine.y == 0 ? game->board.size.y - 1 : 0;
	game->angle_opmine.x = game->angle_target.x;
	game->angle_opmine.y = game->angle_target.y == 0 ? game->board.size.y - 1 : 0;
	game->angle_opadv.x = game->angle_target.x == 0 ? game->board.size.x - 1 : 0;
	game->angle_opadv.y = game->angle_target.y;
}

static enum e_state		board_char_is_ok(t_game *game, char c, int x , int y)
{
	t_point	pos;

	pos.x = x;
	pos.y = y;
	if (c == EMPTY)
		return (E_EMPTY);
	else if (c == P1_CHAR || c == P2_CHAR || c == P1_LAST_CHAR || c == P2_LAST_CHAR)
	{
		if (c == game->my_char || c == game->my_last_char)
		{
			if (game->core_mine.x == 0 && game->core_mine.y == 0)
			{
				game->last_mine = pos;
				game->core_mine = pos;
			}
			return (c == game->my_last_char ? E_LAST_MINE : E_MINE);
		}

		
		if (game->core_adv.x == 0 && game->core_adv.y == 0)
		{
			game->last_adv = pos;
			game->core_adv = pos;
		}
		else if (game->board.mx[x][y] == E_EMPTY || c == game->adv_last_char)
		{
			if ((game->last_adv.x == 0 && game->last_adv.y == 0)
					|| delta(&pos, &game->core_mine)
					< delta(&game->last_adv, &game->core_mine))
				game->last_adv = pos;
			return (E_ADV);
		}
		return (E_ADV);
	}
	else
		return (E_UNKNOW);
}

static enum e_state		piece_char_is_ok(char c)
{
	if (c == EMPTY)
		return (E_EMPTY);
	else if (c == FULL)
		return (E_FULL);
	else
		return (E_UNKNOW);
}

int						get_line_board(t_game *game, char *line)
{
	size_t	y;
	char	row_str[5];

	y = 0;
	row_str[4] = '\0';
	row_str[3] = ' ';
	row_str[2] = game->row % 10 + '0';
	row_str[1] = (game->row / 10) % 10 + '0';
	row_str[0] = game->row / 100 + '0';
	if (ft_strnequ(row_str, line, 4) == FALSE)
		return (FAILURE);
	line += 4;
	if (((int)ft_strlen(line) != game->board.size.y)
			|| (game->row > game->board.size.x))
		return (FAILURE);
	while (line[y] != '\0')
	{
		game->board.mx[game->row][y] = board_char_is_ok(game, line[y], game->row, y);
		if (game->board.mx[game->row][y] == E_UNKNOW)
			return (FAILURE);
		y++;
	}
	if (game->turn == 0)
		get_angle(game);
	return (SUCCESS);
}

int						get_line_piece(t_game *game, char *line)
{
	size_t	y;

	y = 0;
	if (((int)ft_strlen(line) > game->piece.size.y)
			|| (game->row > game->piece.size.x))
		return (FAILURE);
	while (line[y] != '\0')
	{
		game->piece.mx[game->row][y] = piece_char_is_ok(line[y]);
		if (game->piece.mx[game->row][y] == E_UNKNOW)
			return (FAILURE);
		y++;
	}
	return (SUCCESS);
}
