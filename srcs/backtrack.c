/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 11:59:40 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/17 13:07:39 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"



void	init_way(t_game *game)
{
	int		x;
	int		y;

	x = 0;
	while (x < game->board.size.x)
	{
		y = 0;
		while (y < game->board.size.y)
		{
			if (game->board.mx[x][y] == E_EMPTY)
				game->way[x][y] = OPEN; 
			else
				game->way[x][y] = CLOSE; 
			y++;
		}
		x++;
	}
}
