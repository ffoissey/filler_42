#include "filler.h"

void	free_board(t_game *game)
{
	int		x;

	x = 0;
	while (x < game->board_size.x)
	{
		free(game->board[x]);
		game->board[x] = NULL;
		x++;
	}
	free(game->board);
	game->board = NULL;
}

int		main(void)
{
	t_game				game;
	char				*line;
	static	t_process	process[] = {get_player, get_board_size,
									get_board_first_line, get_board,
									get_piece_size, get_piece, speak, error};

	ft_bzero(&game, sizeof(game));
	game.action = E_GET_PLAYER;
	game.core_mine.x = 0;
	game.core_mine.y = 0;
	game.core_adv.x = 0;
	game.core_adv.y = 0;
	line = NULL;
	while (get_next_line_origin(0, &line) > 0)
	{
		process[game.action](&game, &line);
	}
	free_board(&game);
	return (SUCCESS);
}
