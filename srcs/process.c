/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:31:56 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/18 18:31:57 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static unsigned char	pos_is_ok(t_game *game, t_point *pos,
							t_point *p, int *contact)
{
	if (pos->x + p->x < 0 || pos->y + p->y < 0
			|| pos->x + p->x >= game->board.size.x
			|| pos->y + p->y >= game->board.size.y)
	{
		if (game->piece.mx[p->x][p->y] == E_FULL)
			return (FALSE);
	}
	else if ((game->board.mx[pos->x + p->x][pos->y + p->y] == E_ADV
				|| game->board.mx[pos->x + p->x][pos->y + p->y] == E_LAST_ADV)
			&& game->piece.mx[p->x][p->y] == E_FULL)
		return (FALSE);
	else if (*contact > 1)
		return (FALSE);
	else if (((game->board.mx[pos->x + p->x][pos->y + p->y] == E_MINE)
			|| (game->board.mx[pos->x + p->x][pos->y + p->y] == E_LAST_MINE))
			&& game->piece.mx[p->x][p->y] == E_FULL)
	{
		game->contact.x = pos->x + p->x;
		game->contact.y = pos->y + p->y;
		(*contact)++;
	}
	return (TRUE);
}

static unsigned char	check_piece(t_game *game, t_point *pos)
{
	t_point	p;
	int		contact;

	contact = 0;
	p.x = 0;
	while (p.x < game->piece.size.x)
	{
		p.y = 0;
		while (p.y < game->piece.size.y)
		{
			if (pos_is_ok(game, pos, &p, &contact) == FALSE)
				return (FALSE);
			p.y++;
		}
		p.x++;
	}
	return (contact == 1);
}

static void				find_coord(t_game *game, t_strategy strategy)
{
	t_point end;
	t_point	start;
	int		tmp_y;

	start.x = 0 - game->piece.size.x - 1;
	tmp_y = 0 - game->piece.size.y - 1;
	end.x = game->board.size.x + game->piece.size.x;
	end.y = game->board.size.y + game->piece.size.y;
	while (++start.x < end.x)
	{
		start.y = tmp_y;
		while (++start.y < end.y)
		{
			if (check_piece(game, &start) == TRUE)
			{
				if ((game->to_play.x == 0 && game->to_play.y == 0)
					|| strategy(game) == TRUE)
				{
					game->good_contact = game->contact;
					game->to_play = start;
				}
			}
		}
	}
}

void					ft_process(t_game *game)
{
	static	t_strategy	strategy[] = {angle_target_mode, angle_opmine_mode,
										angle_opadv_mode, attack_mode,
										glue_mode};

	ft_bzero(&game->to_play, sizeof(t_point));
	game->nearest_adv = nearest(game);
	chose_better_angle(game);
	select_strategy(game);
	find_coord(game, strategy[game->mode]);
	game->last_mine = game->contact;
	ft_bzero(&game->last_adv, sizeof(t_point));
	ft_bzero(&game->good_contact, sizeof(t_point));
	ft_bzero(&game->contact, sizeof(t_point));
	game->turn++;
}
