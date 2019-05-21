/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:46:19 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/21 13:03:15 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	board(t_game *game, t_point *middle)
{
	t_point	p;

	p.x = -1;
	while (++p.x < game->board.size.x)
	{
		ft_printf("\033[%d;%dH%s", middle->x + p.x, middle->y - 1, GREEN);
		p.y = -1;
		while (++p.y < game->board.size.y)
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
		}
		ft_printf("%s%s\n", GREEN, NC);
	}
	ft_printf("\033[%d;%dH", middle->x + p.x++, middle->y - 1);
}

void	delay(t_game *game)
{
	int		time;

	time = game->delay;
	while (time)
		time--;
}

void	border(t_game *game)
{
	int		i;

	i = 0;
	while (i++ - 1 < game->board.size.y + 1)
		ft_putstr(GREEN);
	ft_putstr(NC);
}

void	player(t_game *game, t_point *middle, struct winsize *w)
{
	ft_printf("\033[%d;%dH", middle->x - 1,
				w->ws_col / 2 + game->board.size.y / 2 + 22
				- ft_strlen(INFO) / 2);
	ft_printf("\033[32;1m%s\033[0m", INFO);
	ft_printf("\033[%d;%dH", middle->x + 1, w->ws_col / 2
			+ game->board.size.y / 2);
	ft_printf("PLAYER 1 |  \033[34;1m%-8.8s\033[0m  | OK -> %s%s  Last -> %s%s",
			game->p1_name, BLUE, NC, CYAN, NC);
	ft_printf("\033[%d;%dH", middle->x + 3, w->ws_col / 2
			+ game->board.size.y / 2);
	ft_printf("PLAYER 2 |  \033[31;1m%-8.8s\033[0m  | OK -> %s%s  Last -> %s%s",
			game->p2_name, RED, NC, YELLOW, NC);
}
