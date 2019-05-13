#include "filler.h"

void	speak(t_game *game, char **line)
{
	(void)line;
	ft_printf("%d %d\n", game->to_play.x, game->to_play.y);
	game->action = E_GET_BOARD_SIZE;
}

void	error(t_game *game, char **line)
{
	(void)line;
	game->action = E_ERROR;
	/// FREE PIECE
	/// FREE BOARD
	ft_putendl_fd("Error", 2);
}

void	get_player(t_game *game, char **line)
{
	if (ft_strequ(*line, PLAYER_ONE) == TRUE)
	{
		game->my_char = P1_CHAR;
		game->my_last_char = P1_LAST_CHAR;
		game->adv_char = P2_CHAR;
		game->adv_last_char = P2_LAST_CHAR;
		game->action = E_GET_BOARD_SIZE;
	}
	else if (ft_strequ(*line, PLAYER_TWO) == TRUE)
	{
		game->my_char = P2_CHAR;
		game->my_last_char = P2_LAST_CHAR;
		game->adv_char = P1_CHAR;
		game->adv_last_char = P1_LAST_CHAR;
		game->action = E_GET_BOARD_SIZE;
	}
	else
		error(game, line);
	ft_strdel(line);
}

void	get_board_size(t_game *game, char **line)
{
	game->row = 0;
	if (get_size(&game->board_size, &game->board, *line, PLATEAU) == FAILURE)
		error(game, line);
	else
		game->action = E_GET_BOARD_FIRST_LINE;
	ft_strdel(line);
}

void	get_piece_size(t_game *game, char **line)
{
	game->row = 0;
	if (get_size(&game->piece_size, &game->piece, *line, PIECE) == FAILURE)
		error(game, line);
	else
		game->action = E_GET_PIECE;
	ft_strdel(line);
}

void	get_board_first_line(t_game *game, char **line)
{
	if (check_first_line_board(game->board_size.x, *line) == FALSE)
		error(game, line);
	else
		game->action = E_GET_BOARD;
	ft_strdel(line);
}

void	get_board(t_game *game, char **line)
{
	if (get_line_board(game, *line) == FAILURE)
		error(game, line);
	else if (game->row < game->board_size.y - 1)
		game->row++;
	else
		game->action = E_GET_PIECE_SIZE;
	ft_strdel(line);
}

void	get_piece(t_game *game, char **line)
{
	if (get_line_piece(game, *line) == FAILURE)
		error(game, line);
	else if (game->row < game->piece_size.y - 1)
		game->row++;
	else
	{
		game->action = E_GET_BOARD_SIZE;
		ft_process(game);
		///free_piece;
		speak(game, line);
	}
	ft_strdel(line);
}
