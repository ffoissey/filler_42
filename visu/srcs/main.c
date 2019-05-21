/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:46:09 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/21 13:01:13 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void		free_matrix(t_mx *mx)
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

static void	exit_routine(t_game *game, char **line)
{
	ft_strdel(line);
	free_matrix(&game->board);
	free_matrix(&game->piece);
	ft_strdel(&game->p1_name);
	ft_strdel(&game->p2_name);
}

int			main(int ac, char **av)
{
	t_game				game;
	char				*line;
	static	t_process	process[] = {get_player, get_size,
									get_board_first_line, get_board, get_size,
									get_piece, get_pos};

	ft_bzero(&game, sizeof(game));
	if (ac == 1)
		game.delay = DELAY;
	else
		game.delay = ft_atoi(av[1]) < 0
			|| ft_strequ("-2147483648", av[1]) ? 0 : ft_atoi(av[1]);
	game.action = E_GET_PLAYER;
	ft_printf("\033[2J");
	line = NULL;
	while (get_next_line(STDIN_FILENO, &line))
	{
		if (game.action == E_ERROR)
			break ;
		process[game.action](&game, &line);
		ft_strdel(&line);
	}
	print_board(&game, (line && ft_strstr(line, "fin")) ? 1 : 2);
	exit_routine(&game, &line);
	return (SUCCESS);
}
