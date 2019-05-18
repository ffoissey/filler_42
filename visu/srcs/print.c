/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:46:14 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/18 18:10:07 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void		set_middle_and_position(t_game *game,
				t_point *middle, struct winsize *w)
{
	middle->x = w->ws_row / 2 - game->board.size.x / 2;
	middle->y = w->ws_col / 2 - game->board.size.y;
	middle->y -= middle->y / 2;
	ft_printf("\033[1;1H");
	ft_printf("\033[%d;%dH", middle->x - 1, middle->y - 1);
}

static void	set_info(t_game *game, t_point *scale)
{
	ft_printf("\033[%d;%dH", scale->x - 1, scale->y);
	ft_printf("\033[32mGame Delay: %d\033[0m", game->delay);
	ft_printf("\033[%d;%dH", scale->x, scale->y);
	ft_printf("P: piece | O: occupation");
	scale->x += 2;
	ft_printf("\033[%d;%dH", scale->x++, scale->y);
	ft_printf("P:\033[34;1m%4d\033[0m", game->nb_piece_p1);
	ft_printf("\033[%d;%dH", scale->x++, scale->y);
	ft_printf("O:\033[34;1m%4d\033[0m", game->last_score_p1);
	ft_printf("\033[%d;%dH", scale->x - 2, scale->y + 38);
	ft_printf("P:\033[31;1m%4d\033[0m", game->nb_piece_p2);
	ft_printf("\033[%d;%dH", scale->x - 1, scale->y + 38);
	ft_printf("O:\033[31;1m%4d\033[0m", game->last_score_p2);
	ft_printf("\033[%d;%dH", scale->x + 1, scale->y);
}

static void	score(t_game *game, t_point *scale)
{
	int		p1;
	int		i;

	i = 0;
	set_info(game, scale);
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
	if (game->nb_piece_p1 > game->nb_piece_p2)
	{
		ft_printf("\033[%d;%dH", scale->x, scale->y + 22
				- (ft_strlen(game->p1_name) + 5) / 2);
		ft_printf("\033[34;1;5m%s WIN!\033[0m", ft_strupcase(game->p1_name));
	}
	else if (game->nb_piece_p1 < game->nb_piece_p2)
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
	delay(game);
	set_middle_and_position(game, &middle, &w);
	border(game);
	board(game, &middle);
	border(game);
	player(game, &middle, &w);
	scale.x = middle.x + 6;
	scale.y = w.ws_col / 2 + game->board.size.y / 2;
	score(game, &scale);
	scale.x += 4;
	end_game(game, &scale, end);
	ft_printf("\033[%d;1H", w.ws_row);
}
