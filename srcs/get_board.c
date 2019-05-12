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

static enum e_state		board_char_is_ok(t_game *game, char c)
{
	if (c == EMPTY)
		return (E_EMPTY);
	else if (c == P1_CHAR)
		return (c == game->my_char ? E_MINE : E_ADV);
	else if (c == P2_CHAR)
		return (c == game->my_char ? E_MINE : E_ADV);
	else if (c == P1_LAST_CHAR)
		return (c == game->my_last_char ? E_LAST_MINE : E_LAST_ADV);
	else if (c == P2_LAST_CHAR)
		return (c == game->my_last_char ? E_LAST_MINE : E_LAST_ADV);
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
	if (ft_strlen(line) != game->board_size.x)
		return (FAILURE);
	while (line[i] != '\0')
	{
		game->board[game->row][i] = board_char_is_ok(game, line[i]);
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
	if (ft_strlen(line) != game->piece_size.x)
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
