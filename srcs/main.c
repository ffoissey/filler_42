#include "filler.h"
#include "libft.h"

void	get_player(t_game *game, char *line)
{
	if (ft_strequ(line, PLAYER_ONE) == TRUE)
	{
		game->my_char = P1_CHAR;
		game->my_last_char = P1_LAST_CHAR;
		game->adv_char = P2_CHAR;
		game->adv_last_char = P2_LAST_CHAR;
	}
	else if (ft_strequ(line, PLAYER_TWO) == TRUE)
	{
		game->my_char = P2_CHAR;
		game->my_last_char = P2_LAST_CHAR;
		game->adv_char = P1_CHAR;
		game->adv_last_char = P1_LAST_CHAR;
	}
}

void	get_board(t_game *game, char *line)
{
	(void)game;
	(void)line;
}

void	get_piece(t_game *game, char *line)
{
	(void)game;
	(void)line;
}

int		main(void)
{
	t_game				game;
	char				*line;
	static	t_process	process[] = {	get_player,
										get_board,
										get_piece,
									};
	bzero(&game, sizeof(game));
	game.action = E_GET_PLAYER;
	while (42)
	{
		while (get_next_line(STDIN_FILENO, &line) > 0)
		{
			process[game.action](&game, line);
			ft_strdel(&line);
		}
	}
	return (SUCCESS);
}
