/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:28:11 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/18 18:49:16 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static enum e_state		which_char(t_game *game, char c, t_point pos)
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
	else if (game->board.mx[pos.x][pos.y] == E_EMPTY
			|| c == game->adv_last_char)
	{
		if ((game->last_adv.x == 0 && game->last_adv.y == 0)
				|| delta(&pos, &game->core_mine)
				< delta(&game->last_adv, &game->core_mine))
			game->last_adv = pos;
		return (E_LAST_ADV);
	}
	return (E_ADV);
}

static enum e_state		board_char_is_ok(t_game *game, char c, int x, int y)
{
	t_point	pos;

	pos.x = x;
	pos.y = y;
	if (c == EMPTY)
		return (E_EMPTY);
	else if (c == P1_CHAR || c == P2_CHAR
			|| c == P1_LAST_CHAR || c == P2_LAST_CHAR)
		return (which_char(game, c, pos));
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
		game->board.mx[game->row][y] = board_char_is_ok(game,
											line[y], game->row, y);
		if (game->board.mx[game->row][y] == E_UNKNOW)
			return (FAILURE);
		y++;
	}
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
