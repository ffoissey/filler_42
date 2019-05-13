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

static enum e_state		board_char_is_ok(t_game *game, char c, int i , int j)
{
	t_point	pos;

	pos.x = i;
	pos.y = j;
	if (c == EMPTY)
		return (E_EMPTY);
	else if (c == P1_CHAR || c == P2_CHAR)
	{
		if (c == game->my_char)
		{
			if (game->core_mine.x == -1)
			{
				game->last_mine.y = j;
				game->last_mine.x = i;
				game->core_mine.y = j;
				game->core_mine.x = i;
			}
			return (E_MINE);
		}
		if (game->core_adv.x == -1)
		{
				game->last_adv.y = j;
				game->last_adv.x = i;
				game->core_adv.y= j;
				game->core_adv.x = i;
		}
		return (E_ADV);
	}
	else if (c == P1_LAST_CHAR || c == P2_LAST_CHAR)
	{
		if (c == game->my_last_char)
			return (E_LAST_MINE);
		if (game->last_adv.x)
		{
			if (game->last_adv.x == -1
				|| get_delta(&pos, &game->core_mine) < get_delta(&game->last_adv, &game->core_mine))
			{
				game->last_adv.y = j;
				game->last_adv.x = i;
			}
		}
		return (E_LAST_ADV);
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
	size_t	i;
	char	row_str[5];

	i = 0;
	row_str[4] = '\0';
	row_str[3] = ' ';
	row_str[2] = game->row % 10 + '0';
	row_str[1] = (game->row / 10) % 10 + '0';
	row_str[0] = game->row / 100 + '0';
	if (ft_strnequ(row_str, line, 4) == FALSE)
		return (FAILURE);
	line += 4;
	if (((int)ft_strlen(line) != game->board_size.x)
		|| (game->row > game->board_size.y))
		return (FAILURE);
	while (line[i] != '\0')
	{
		game->board[game->row][i] = board_char_is_ok(game, line[i], i , game->row);
		if (game->board[game->row][i] == E_UNKNOW)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int						get_line_piece(t_game *game, char *line)
{
	size_t	i;

	i = 0;
	if (((int)ft_strlen(line) != game->piece_size.x)
		|| (game->row > game->piece_size.y))
		return (FAILURE);
	while (line[i] != '\0')
	{
		game->piece[game->row][i] = piece_char_is_ok(line[i]);
		if (game->piece[game->row][i] == E_UNKNOW)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
