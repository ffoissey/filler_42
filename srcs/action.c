#include "filler.h"

void	get_player(t_game *game, char **line)
{
	if (ft_strnequ(*line, PLAYER_ONE, PLAYER_SIZE) == TRUE
			&& (ft_strstr(*line, game->process_name) != NULL))
	{
		game->my_char = P1_CHAR;
		game->my_last_char = P1_LAST_CHAR;
		game->adv_char = P2_CHAR;
		game->adv_last_char = P2_LAST_CHAR;
		game->action = E_GET_BOARD_SIZE;
	}
	else if (ft_strnequ(*line, PLAYER_TWO, PLAYER_SIZE) == TRUE
			&& (ft_strstr(*line, game->process_name) != NULL))
	{
		game->my_char = P2_CHAR;
		game->my_last_char = P2_LAST_CHAR;
		game->adv_char = P1_CHAR;
		game->adv_last_char = P1_LAST_CHAR;
		game->action = E_GET_BOARD_SIZE;
	}
	else
		error(game, line);
}

void	get_size(t_game *game, char **line)
{
	game->row = 0;
	if (game->action == E_GET_PIECE_SIZE)
	{
		if (process_size(&game->piece.size, &game->piece.mx, *line, PIECE)
				== FAILURE)
			error(game, line);
		else
			game->action = E_GET_PIECE;
	}
	else
	{
		if (process_size(&game->board.size, &game->board.mx, *line, PLATEAU)
				== FAILURE)
			error(game, line);
		else
			game->action = E_GET_BOARD_FIRST_LINE;
	}
}

void	get_board_first_line(t_game *game, char **line)
{
	if (check_first_line_board(game->board.size.y, *line) == FALSE)
		error(game, line);
	else
		game->action = E_GET_BOARD;
}

void	get_board(t_game *game, char **line)
{
	if (game->row + 1 == game->board.size.x)
	{
		if (get_line_board(game, *line) == FAILURE)
			error(game, line);
		else
			game->action = E_GET_PIECE_SIZE;
	}
	else if (get_line_board(game, *line) == FAILURE)
		error(game, line);
	else
		game->row++;
}

void	get_piece(t_game *game, char **line)
{
	if (game->row + 1 == game->piece.size.x)
	{
		if (get_line_piece(game, *line) == FAILURE)
			error(game, line);
		else
		{
			game->to_play.x = 0;
			game->to_play.y = 0;
			ft_process(game);
			speak(game, line);
			game->action = E_GET_BOARD_SIZE;
		}
	}
	else if (get_line_piece(game, *line) == FAILURE)
		error(game, line);
	else
		game->row++;
}
