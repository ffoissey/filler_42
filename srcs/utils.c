/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:35:57 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/21 13:06:40 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			speak(t_game *game, char **line)
{
	ft_strdel(line);
	free_matrix(&game->piece);
	ft_printf("%d %d\n", game->to_play.x, game->to_play.y);
	game->action = E_GET_BOARD_SIZE;
}

void			error(t_game *game, char **line)
{
	ft_strdel(line);
	free_matrix(&game->piece);
	free_matrix(&game->board);
	game->action = E_ERROR;
	if (game->error == 0)
	{
		game->error = 1;
		ft_putendl_fd("Error", 2);
	}
}

void			free_matrix(t_mx *mx)
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

int				delta(t_point *a, t_point *b)
{
	return ((b->x - a->x)) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y);
}

unsigned char	check_first_line_board(unsigned int row, char *line)
{
	size_t	i;
	size_t	max;
	size_t	count;

	i = 0;
	max = row + 4;
	if (ft_strlen(line) != max)
		return (FALSE);
	while (i < 4)
	{
		if (line[i] != ' ')
			return (FALSE);
		i++;
	}
	count = 0;
	while (i < max)
	{
		if (count % 10 + '0' != line[i])
			return (FALSE);
		count++;
		i++;
	}
	return (TRUE);
}
