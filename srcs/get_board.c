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

static void				get_angle(t_game *game)
{
	if (game->board_size.x - game->core_adv.x > game->board_size.x / 2)
		game->angle.x = 0;
	else
		game->angle.x = game->board_size.x;
	if (game->board_size.y - game->core_adv.y > game->board_size.y / 2)
		game->angle.y = 0;
	else
		game->angle.y = game->board_size.y;
	game->core_up.x = game->core_adv.x;
	game->core_up.y = game->angle.y;
	game->core_side.x = game->angle.x;
	game->core_side.y = game->core_adv.y;
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
			if (game->core_mine.x == 0 && game->core_mine.x == 0)
			{
				game->last_mine.y = y;
				game->last_mine.x = x;
				game->core_mine.y = y;
				game->core_mine.x = x;
			}
			return (c == game->my_last_char ? E_LAST_MINE : E_MINE);
		}
		if (game->core_adv.x == 0 && game->core_adv.y == 0)
		{
			game->last_adv.y = y;
			game->last_adv.x = x;
			game->core_adv.y = y;
			game->core_adv.x = x;
			get_angle(game);
		}
		else if (game->board[x][y] == E_EMPTY)
		{
			if ((game->last_adv.x == 0 && game->last_adv.y == 0)
					|| get_delta(&pos, &game->core_mine) < get_delta(&game->last_adv, &game->core_mine))
			{
				game->last_adv.y = y;
				game->last_adv.x = x;
			}
			return (E_LAST_ADV);
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
	if (((int)ft_strlen(line) != game->board_size.y)
			|| (game->row > game->board_size.x))
		return (FAILURE);
	while (line[y] != '\0')
	{
		game->board[game->row][y] = board_char_is_ok(game, line[y], game->row, y);
		if (game->board[game->row][y] == E_UNKNOW)
			return (FAILURE);
		y++;
	}
	return (SUCCESS);
}

int						get_line_piece(t_game *game, char *line)
{
	size_t	y;

	y = 0;
	if (((int)ft_strlen(line) > game->piece_size.y)
			|| (game->row > game->piece_size.x))
		return (FAILURE);
	while (line[y] != '\0')
	{
		game->piece[game->row][y] = piece_char_is_ok(line[y]);
		if (game->piece[game->row][y] == E_UNKNOW)
			return (FAILURE);
		y++;
	}
	return (SUCCESS);
}
