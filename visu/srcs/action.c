#include "visu.h"

void	get_player(t_game *game, char **line)
{
	if (*line == NULL
		|| (ft_strstr(*line, "Error") != NULL
		&& ft_strstr(*line, "filler") == NULL))
		game->action = E_ERROR;
	else if (ft_strnequ(PLAYER_ONE, *line, PLAYER_SIZE) == TRUE)
		game->p1_name = ft_strcdup(ft_strrchr(*line, '/') + 1, '.');
	else if (ft_strnequ(PLAYER_TWO, *line, PLAYER_SIZE) == TRUE)
		game->p2_name = ft_strcdup(ft_strrchr(*line, '/') + 1, '.');
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
		if (process_size(&game->board.size, &game->board.mx, *line, PLATEAU)
				== FAILURE)
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

void	get_board(t_game *game, char **line)
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

void	get_piece(t_game *game, char **line)
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

void	get_pos(t_game *game, char **line)
{
	char	*tmp;

	if (ft_strnequ(GOT_P1, *line, GOT_SIZE) == TRUE
		|| ft_strnequ(GOT_P2, *line, GOT_SIZE) == TRUE)
	{
		tmp = ft_strchr(*line, '[');
		if (tmp != NULL)
		{
			tmp++;
			game->last_pos.x = ft_atoi(tmp);
		}
		tmp = ft_strchr(*line, ',');
		if (tmp != NULL)
		{
			tmp++;
			game->last_pos.y = ft_atoi(tmp);
		}
		if (game->turn != 0 && game->turn != 1)
		{
			if (game->last_score_p1 != game->score_p1)
				game->nb_piece_p1++;
			if (game->last_score_p2 != game->score_p2)
				game->nb_piece_p2++;
		}
		if (game->score_p1 != 0)
			game->last_score_p1 = game->score_p1;
		if (game->score_p2 != 0)
			game->last_score_p2 = game->score_p2;
		game->score_p1 = 0;
		game->score_p2 = 0;
		game->turn++;
		print_board(game, 0);
		game->action = E_GET_BOARD_SIZE;
	}
	else
		game->action = E_ERROR;
	free_matrix(&game->piece);
}
