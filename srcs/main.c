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
	game.core_mine.x = -1;
	game.core_mine.y = -1;
	game.core_adv.x = -1;
	game.core_adv.y = -1;
	while (42)
	{
		line = NULL;
		game.last_adv.x = -1;
		game.last_adv.y = -1;
		game.to_play.x = -1;
		game.to_play.y = -1;
		while (get_next_line_origin(STDIN_FILENO, &line) > 0)
			process[game.action](&game, &line);
	}
	return (SUCCESS);
}
