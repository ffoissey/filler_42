/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:45:55 by ffoissey          #+#    #+#             */
/*   Updated: 2020/05/02 23:15:49 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void		get_board(t_game *game, char **line)
{
	if (game->row + 1 == game->board.size.x)
	{
		if (get_line_board(game, *line) == FAILURE)
			game->action = E_ERROR;
		else
			game->action = E_GET_PIECE_SIZE;
	}
	else if (get_line_board(game, *line) == FAILURE)
		game->action = E_ERROR;
	else
		game->row++;
}

void		get_piece(t_game *game, char **line)
{
	if (game->row + 1 == game->piece.size.x)
	{
		if (get_line_piece(game, *line) == FAILURE)
			game->action = E_ERROR;
		else
			game->action = E_GET_POS;
	}
	else if (get_line_piece(game, *line) == FAILURE)
		game->action = E_ERROR;
	else
		game->row++;
}

static void	set_score(t_game *game)
{
	if (game->last_score_p1 > 1 && game->last_score_p1 != game->score_p1)
		game->nb_piece_p1++;
	if (game->last_score_p2 > 1 && game->last_score_p2 != game->score_p2)
		game->nb_piece_p2++;
	if (game->score_p1 != 0)
		game->last_score_p1 = game->score_p1;
	if (game->score_p2 != 0)
		game->last_score_p2 = game->score_p2;
	game->score_p1 = 0;
	game->score_p2 = 0;
	game->turn++;
}

void		get_pos(t_game *game, char **line)
{
	const char	*tmp;

	if (ft_strnequ(GOT_P1, *line, GOT_SIZE) == TRUE
			|| ft_strnequ(GOT_P2, *line, GOT_SIZE) == TRUE)
	{
		tmp = ft_strchr(*line, '[');
		if (tmp != NULL)
			game->last_pos.x = ft_atoi(++tmp);
		tmp = ft_strchr(*line, ',');
		if (tmp != NULL)
			game->last_pos.y = ft_atoi(++tmp);
		set_score(game);
		print_board(game, 0);
		game->action = E_GET_BOARD_SIZE;
	}
	else if (*line && ft_strstr(*line, "error") != NULL)
		game->action = E_GET_PIECE_SIZE;
	else
		game->action = E_ERROR;
	free_matrix(&game->piece);
}
