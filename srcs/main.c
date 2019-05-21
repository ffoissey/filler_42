/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:31:47 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/21 12:58:39 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		main(int ac, char **av)
{
	t_game				game;
	char				*line;
	static	t_process	process[] = {get_player, get_size,
									get_board_first_line, get_board,
									get_size, get_piece, speak, error};

	(void)ac;
	ft_bzero(&game, sizeof(game));
	game.action = E_GET_PLAYER;
	game.process_name = av[0];
	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		process[game.action](&game, &line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	free_matrix(&game.board);
	return (SUCCESS);
}
