/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:45:51 by ffoissey          #+#    #+#             */
/*   Updated: 2020/05/02 23:15:27 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	get_player(t_game *game, char **line)
{
	if (*line == NULL
		|| (ft_strstr(*line, "Error") != NULL
		&& ft_strstr(*line, "filler") == NULL))
		game->action = E_ERROR;
	else if (ft_strnequ(PLAYER_ONE, *line, PLAYER_SIZE) == TRUE)
		game->p1_name = ft_strcdup((char *)ft_strrchr(*line, '/') + 1, '.');
	else if (ft_strnequ(PLAYER_TWO, *line, PLAYER_SIZE) == TRUE)
		game->p2_name = ft_strcdup((char *)ft_strrchr(*line, '/') + 1, '.');
	if (game->p1_name != NULL && game->p2_name != NULL)
		game->action = E_GET_BOARD_SIZE;
	else if (ft_strstr(*line, PLATEAU) != NULL)
	{
		game->action = E_GET_BOARD_SIZE;
		get_size(game, line);
	}
}

void	get_size(t_game *game, char **line)
{
	game->row = 0;
	if (game->action == E_GET_PIECE_SIZE)
	{
		if (process_size(&game->piece.size, &game->piece.mx, *line, PIECE)
				== FAILURE)
			game->action = E_ERROR;
		else
			game->action = E_GET_PIECE;
	}
	else
	{
		if (process_size(&game->board.size, &game->board.mx,
					*line, PLATEAU) == FAILURE)
		{
			game->action = E_GET_PIECE_SIZE;
			get_size(game, line);
		}
		else
			game->action = E_GET_BOARD_FIRST_LINE;
	}
}

void	get_board_first_line(t_game *game, char **line)
{
	if (check_first_line_board(game->board.size.y, *line) == FALSE)
		game->action = E_ERROR;
	else
		game->action = E_GET_BOARD;
}
