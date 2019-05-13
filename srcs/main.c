#include "filler.h"

#include "fcntl.h"
int		main(void)
{
	t_game				game;
	char				*line;
	static	t_process	process[] = {get_player, get_board_size,
									get_board_first_line, get_board,
									get_piece_size, get_piece, speak, error};
	static	const char	*action[] = {"get_player", "get_board_size",
									"get_board_first_line", "get_board",
									"get_piece_size", "get_piece", "speak", "error"};
	int		fd;

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
		fd = open("hey", O_RDWR);
		while (get_next_line_origin(0, &line) > 0)
		{
			ft_dprintf(fd, "LINE: %s\nGAME ACTION: %s\n", line, action[game.action]);
			process[game.action](&game, &line);
		}
		game.action = E_GET_BOARD_SIZE;
	}
	close(fd);
	return (SUCCESS);
}
