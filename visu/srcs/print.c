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
			if (game->board.mx[p.x][p.y] == E_LAST_P1
				|| (p.x == game->core_p1.x && p.y == game->core_p1.y))
				ft_putstr(CYAN);
			else if (game->board.mx[p.x][p.y] == E_LAST_P2
				|| (p.x == game->core_p2.x && p.y == game->core_p2.y))
				ft_putstr(YELLOW);
			else if (game->board.mx[p.x][p.y] == E_P1)
				ft_putstr(BLUE);
			else if (game->board.mx[p.x][p.y] == E_P2)
				ft_putstr(RED);
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
	ft_printf("\033[%d;%dH", middle->x - 1,
				w->ws_col / 2 + game->board.size.y / 2 + 22
				- ft_strlen(INFO) / 2);
	ft_printf("\033[32;1m%s\033[0m", INFO);
	ft_printf("\033[%d;%dH", middle->x + 1, w->ws_col / 2
			+ game->board.size.y / 2);
	ft_printf("PLAYER 1 |  \033[34;1m%-8s\033[0m  | OK -> %s%s  Last -> %s%s",
			game->p1_name, BLUE, NC, CYAN, NC);
	ft_printf("\033[%d;%dH", middle->x + 3, w->ws_col / 2
			+ game->board.size.y / 2);
	ft_printf("PLAYER 2 |  \033[31;1m%-8s\033[0m  | OK -> %s%s  Last -> %s%s",
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

static void	score(t_game *game, t_point *scale)
{
	int		p1;
	int		i;

	i = 0;
	ft_printf("\033[%d;%dH", scale->x, scale->y);
	ft_printf("\033[34;1m%-4d\033[0m\n", game->last_score_p1);
	ft_printf("\033[%d;%dH", scale->x, scale->y + 40);
	ft_printf("\033[31;1m%4d\033[0m\n", game->last_score_p2);
	ft_printf("\033[%d;%dH", scale->x + 2, scale->y);
	if (game->last_score_p1 == 0 && game->last_score_p2 == 0)
		p1 = 22;
	else if (game->last_score_p1 == 0 || game->last_score_p2 == 0)
		p1 = game->last_score_p1 == 0 ? 0 : LEN_P;
	else
		p1 = game->last_score_p1 * LEN_P
			/ (game->last_score_p1 + game->last_score_p2);
	while (i < LEN_P)
	{
		if (i == p1)
			ft_putstr(PURPLE);
		else
			ft_putstr(i < p1 ? BLUE_ONE : RED_ONE);
		i++;
	}
	ft_putstr(NC);
}

static void	end_game(t_game *game, t_point *scale, int end)
{
	if (end == 0)
		return ;
	if (end == 2)
	{
		ft_printf("\033[%d;%dH", scale->x, scale->y + 19);
		ft_printf("\033[0;1mERROR !\033[0m");
		return ;
	}
	if (game->last_score_p1 > game->last_score_p2)
	{
		ft_printf("\033[%d;%dH", scale->x, scale->y + 22
				- (ft_strlen(game->p1_name) + 5) / 2);
		ft_printf("\033[34;1;5m%s WIN!\033[0m", ft_strupcase(game->p1_name));
	}
	else if (game->last_score_p1 > game->last_score_p2)
	{
		ft_printf("\033[%d;%dH", scale->x, scale->y + 22
				- (ft_strlen(game->p2_name) + 5) / 2);
		ft_printf("\033[31;1;5m%s WIN!\033[0m", ft_strupcase(game->p2_name));
	}
	else
	{
		ft_printf("\033[%d;%dH", scale->x, scale->y + 17);
		ft_printf("\033[32;1mEQUALITY !\033[0m");
	}
}

void		print_board(t_game *game, int end)
{
	t_point			middle;
	t_point			scale;
	struct winsize	w;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == FAILURE)
		return ;
	delay();
	set_middle_and_position(game, &middle, &w);
	border(game);
	board(game, &middle);
	border(game);
	player(game, &middle, &w);
	scale.x = middle.x + 6;
	scale.y = w.ws_col / 2 + game->board.size.y / 2;
	score(game, &scale);
	scale.x += 5;
	end_game(game, &scale, end);
	//ft_printf("\033[u");
	ft_printf("\033[%d;1H", w.ws_row);
}
