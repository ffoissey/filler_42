#include "filler.h"

void	speak(t_game *game, char **line)
{
	ft_printf("%d %d\n", game->to_play.x, game->to_play.y);
	game->action = E_GET_BOARD_SIZE;
	ft_strdel(line);
}

void	error(t_game *game, char **line)
{
	ft_strdel(line);
	game->action = E_ERROR;
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
		ft_strdel(line);
	}
	else if (ft_strequ(*line, PLAYER_TWO) == TRUE)
	{
		game->my_char = P2_CHAR;
		game->my_last_char = P2_LAST_CHAR;
		game->adv_char = P1_CHAR;
		game->adv_last_char = P1_LAST_CHAR;
		game->action = E_GET_BOARD_SIZE;
		ft_strdel(line);
	}
	else
		error(game, line);
}

void	get_board_size(t_game *game, char **line)
{
	if (get_size(&game->board_size, *line, PLATEAU) == FAILURE)
		error(game, line);
	else
	{
		game->action = E_GET_BOARD;
		ft_strdel(line);
	}
}

void	get_piece_size(t_game *game, char **line)
{
	if (get_size(&game->piece_size, *line, PLATEAU) == FAILURE)
		error(game, line);
	else
	{
		game->action = E_GET_BOARD;
		ft_strdel(line);
	}
}

void	get_board(t_game *game, char **line)
{
	(void)game;
	if (check_first_line_board(game->board_size.y, *line) == FALSE)
		error(game, line);
	else
	{
		ft_putendl("OK");
		ft_strdel(line);
	}
}

void	get_piece(t_game *game, char **line)
{
	(void)game;
	ft_strdel(line);
}
