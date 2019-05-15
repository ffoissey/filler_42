#include "visu.h"

void	free_matrix(t_mx *mx)
{
	int		x;

	x = 0;
	while (x < mx->size.x)
	{
		free(mx->mx[x]);
		mx->mx[x] = NULL;
		x++;
	}
	free(mx->mx);
	mx->mx = NULL;
	mx->size.x = 0;
	mx->size.y = 0;
}

int		main(void)
{
	t_game	game;
	char	*line;
	static	t_process	process[] = {get_player, get_size,
									get_board_first_line, get_board, get_size,
									get_piece, get_pos};

	ft_bzero(&game, sizeof(game));
	game.action = E_GET_PLAYER;
	ft_printf("\033[2J");
	line = NULL;
	while (get_next_line(STDIN_FILENO, &line))
	{
		process[game.action](&game, &line);
		if (game.action == E_ERROR)
			break ;
		ft_strdel(&line);
	}
	if (line && ft_strstr(line, "fin") != NULL)
		print_board(&game, 1);
	else
		print_board(&game, 2);
	ft_strdel(&line);
	free_matrix(&game.board);
	free_matrix(&game.piece);
	ft_strdel(&game.p1_name);
	ft_strdel(&game.p2_name);
	return (SUCCESS);
}
