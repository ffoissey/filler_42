#include "visu.h"



static void	board(t_game *game, t_point *middle)
{
	t_point	p;

	p.x = 0;
	while (p.x < game->board.size.x)
	{
		ft_printf("\033[%d;%dH%s",middle->x + p.x, middle->y - 1, GREEN);
		p.y = 0;
		while (p.y < game->board.size.y)
		{
			if (game->board.mx[p.x][p.y] == E_P1)
				ft_putstr(BLUE);
			else if (game->board.mx[p.x][p.y] == E_LAST_P1)
				ft_putstr(CYAN);
			else if (game->board.mx[p.x][p.y] == E_P2)
				ft_putstr(RED);
			else if (game->board.mx[p.x][p.y] == E_LAST_P2)
				ft_putstr(YELLOW);
			else
				ft_putstr(WHITE);
			p.y++;
		}
		ft_printf("%s%s\n", GREEN,NC);
		p.x++;
	}
	ft_printf("\033[%d;%dH", middle->x + p.x++, middle->y - 1);
}

static void	delay(void)
{
	int		time;

	time = DELAY;
	while (time)
		time--;
}

static void	border(t_game *game)
{
	int		i;

	i = 0;
	while (i++ - 1 < game->board.size.y + 1)
		ft_putstr(GREEN);
	ft_putstr(NC);
}

static void	player(t_game *game, t_point *middle, struct winsize *w)
{
	ft_printf("\033[%d;%dH", middle->x, w->ws_col / 2 + game->board.size.y / 2);
	ft_printf("PLAYER 1 |  \033[36;1m%s\033[0m  | OK -> %s%s Last -> %s%s",
			game->p1_name, BLUE, NC, CYAN, NC);
	ft_printf("\033[%d;%dH", middle->x + 2, w->ws_col / 2
			+ game->board.size.y / 2);
	ft_printf("PLAYER 2 |  \033[31;1m%s\033[0m  | OK -> %s%s Last -> %s%s\n",
			game->p2_name, RED, NC, YELLOW, NC);
}

static void	set_middle_and_position(t_game *game,
				t_point *middle, struct winsize *w)
{
	middle->x = w->ws_row / 2 - game->board.size.x / 2;
	middle->y = w->ws_col / 2 - game->board.size.y;
	middle->y -= middle->y / 2;
	ft_printf("\033[2J\033[1;1H");
	ft_printf("\033[%d;%dH",middle->x - 1, middle->y - 1);
}

void		print_board(t_game *game)
{
	t_point			middle;
	struct winsize	w;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == FAILURE)
		return ;
	delay();
	set_middle_and_position(game, &middle, &w);
	border(game);
	board(game, &middle);
	border(game);
	player(game, &middle, &w);
	ft_printf("\033[%d;%dH", w.ws_row, w.ws_col);
}
