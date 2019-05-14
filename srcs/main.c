#include "filler.h"

int		main(void)
{
	t_game				game;
	char				*line;
	static	t_process	process[] = {get_player, get_board_size,
									get_board_first_line, get_board,
									get_piece_size, get_piece, speak, error};

	ft_bzero(&game, sizeof(game));
	game.action = E_GET_PLAYER;
	line = NULL;
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		process[game.action](&game, &line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	free_matrix(&game.board);
	return (SUCCESS);
}
