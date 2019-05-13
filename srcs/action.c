#include "filler.h"

void	free_piece(t_game *game)
{
	int		x;

	x = 0;
	while (x < game->piece_size.x)
	{
		free(game->piece[x]);
		game->piece[x] = NULL;
		x++;
	}
	free(game->piece);
	game->piece = NULL;
	game->piece_size.x = 0;
	game->piece_size.y = 0;
}

void	speak(t_game *game, char **line)
{
	(void)line;
	free_piece(game);
	if (game->to_play.x != game->piece_size.x + game->board_size.x
		&& game->to_play.y != game->piece_size.y + game->board_size.y)
	{
		ft_printf("%d %d\n", game->to_play.x, game->to_play.y);
		game->to_play.x = 0;
		game->to_play.y = 0;
	}
	else
	{
		ft_printf("0 0\n");
		ft_printf("\n");
	}
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
	game->last_adv.x = 0;
	game->last_adv.y = 0;
	game->row = 0;
	if (game->board == NULL)
	{
		if (get_size(&game->board_size, &game->board, *line, PLATEAU) == FAILURE)
			error(game, line);
		else
			game->action = E_GET_BOARD_FIRST_LINE;
	}
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
	if (check_first_line_board(game->board_size.y, *line) == FALSE)
		error(game, line);
	else
		game->action = E_GET_BOARD;
	ft_strdel(line);
}

void	get_board(t_game *game, char **line)
{
	if (game->row + 1 == game->board_size.x)
	{
		if (get_line_board(game, *line) == FAILURE)
		{
			error(game, line);
		}
		else
		{
			if (game->delta.advcore_to_mycore == 0)
			{
				game->delta.advcore_to_mycore = get_delta(&game->core_adv, &game->core_mine);
				game->delta.advcore_to_mylast = game->delta.advcore_to_mycore;
				game->delta.advlast_to_mycore = game->delta.advcore_to_mycore;
				game->delta.advlast_to_mylast = game->delta.advcore_to_mycore;
			}
			else
			{
				game->delta.advlast_to_mycore = get_delta(&game->last_adv, &game->core_mine);
				game->delta.advcore_to_mylast = get_delta(&game->core_adv, &game->last_mine);
				game->delta.advlast_to_mylast = get_delta(&game->last_adv, &game->last_mine);
			}
			game->action = E_GET_PIECE_SIZE;
		}
	}
	else if (get_line_board(game, *line) == FAILURE)
		error(game, line);
	else
		game->row++;
	ft_strdel(line);
}

void	get_piece(t_game *game, char **line)
{
	if (game->row + 1 == game->piece_size.x)
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
	ft_strdel(line);
}
