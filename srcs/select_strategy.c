/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_strategy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:34:46 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/18 18:35:46 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			print_strategy(t_game *game)
{
	if (game->mode == E_ANGLE_TARGET)
		ft_dprintf(2, "\033[34mAngle TARGET\033[0m\n");
	else if (game->mode == E_ANGLE_OPMINE)
		ft_dprintf(2, "\033[35mAngle OPMINE\033[0m\n");
	else if (game->mode == E_ANGLE_OPADV)
		ft_dprintf(2, "\033[36mAngle OPADV\033[0m\n");
	else if (game->mode == E_ATTACK)
		ft_dprintf(2, "\033[31mAttack\033[0m\n");
	else if (game->mode == E_GLUE)
		ft_dprintf(2, "\033[37mGlue\033[0m\n");
}

unsigned char	check_angles(t_game *game)
{
	if (game->better_angle == E_NO_ANGLE)
		return (FALSE);
	if (game->better_angle == E_ANGLE_TARGET
		&& over(game, &game->angle_target, E_MINE, 1) == FALSE
		&& scanner(game, &game->angle_target, E_ADV, 1) == FALSE
		&& over(game, &game->angle_target, E_EMPTY, 6) == TRUE)
		game->mode = E_ANGLE_TARGET;
	else if (game->better_angle == E_ANGLE_OPMINE
		&& over(game, &game->angle_opmine, E_MINE, 1) == FALSE
		&& scanner(game, &game->angle_opmine, E_ADV, 1) == FALSE
		&& over(game, &game->angle_opmine, E_EMPTY, 3) == TRUE)
		game->mode = E_ANGLE_OPMINE;
	else if (game->better_angle == E_ANGLE_OPADV
		&& over(game, &game->angle_opadv, E_MINE, 1) == FALSE
		&& scanner(game, &game->angle_opadv, E_ADV, 1) == FALSE
		&& over(game, &game->angle_opadv, E_EMPTY, 6) == TRUE)
		game->mode = E_ANGLE_OPADV;
	else
		return (FALSE);
	return (TRUE);
}

/*
** add print_strategy(game)
** to read the current strategy
** on std_err
*/

void			select_strategy(t_game *game)
{
	if ((scanner(game, &game->last_adv, E_MINE, 3) == TRUE
		|| delta(&game->angle_mine, &game->last_adv)
		< delta(&game->angle_mine, &game->last_mine))
		&& game->board.size.x * game->board.size.y > 500
		&& over(game, &game->last_adv, E_EMPTY, 2) == TRUE)
		game->mode = E_GLUE;
	else if (check_angles(game) == FALSE)
		game->mode = E_ATTACK;
}
