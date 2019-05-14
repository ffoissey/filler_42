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

void	print_board(t_game *game)
{
	int		x;
	int		y;
	int		i;

	i = DELAY;
	while (i)
		i--;
	//system("clear");
	ft_putstr("\033[2J\033[1;40H");
	x = 0;
	while (x < game->board.size.x)
	{
		y = 0;
		while (y < game->board.size.y)
		{
			if (game->board.mx[x][y] == E_P1)
				ft_putstr(BLUE);
			else if (game->board.mx[x][y] == E_LAST_P1)
				ft_putstr(CYAN);
			else if (game->board.mx[x][y] == E_P2)
				ft_putstr(RED);
			else if (game->board.mx[x][y] == E_LAST_P2)
				ft_putstr(PINK);
			else
				ft_putstr(WHITE);
			y++;
		}
		ft_printf("%s\n", NC);
		x++;
	}
	ft_printf("\nP1(0) -> [%s%s][%s%s]\n", BLUE, NC, CYAN, NC);
	ft_printf("P2(X) -> [%s%s][%s%s]\n", RED, NC, PINK, NC);
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
	line = NULL;
	while (get_next_line(STDIN_FILENO, &line) && game.action != E_ERROR)
	{
		process[game.action](&game, &line);
		ft_strdel(&line);	
	}
	ft_strdel(&line);
	free_matrix(&game.board);
	free_matrix(&game.piece);
	ft_strdel(&game.p1_name);
	ft_strdel(&game.p2_name);
	if (game.action == E_ERROR)
		ft_printf(ERROR);
	else
		ft_printf(WINNER);
//	free_mlx;
	return (SUCCESS);
}
