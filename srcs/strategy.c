/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:37:35 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/18 18:37:42 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

unsigned char	angle_target_mode(t_game *game)
{
	if (over(game, &game->contact, E_ADV, 3) == FALSE
			&& over(game, &game->contact, E_MINE, 5) == FALSE)
	{
		if (over(game, &game->good_contact, E_ADV, 3) == TRUE
				|| over(game, &game->good_contact, E_MINE, 5) == TRUE)
			return (TRUE);
		if (game->nearest_adv.x > game->board.size.x / 2)
		{
			if (delta(&game->contact, &game->angle_target)
					<= delta(&game->good_contact, &game->angle_target))
				return (TRUE);
		}
		else
		{
			if (delta(&game->contact, &game->angle_target)
					< delta(&game->good_contact, &game->angle_target))
				return (TRUE);
		}
	}
	return (FALSE);
}

unsigned char	angle_opmine_mode(t_game *game)
{
	if (over(game, &game->contact, E_ADV, 3) == FALSE
			&& over(game, &game->contact, E_MINE, 5) == FALSE)
	{
		if (over(game, &game->good_contact, E_ADV, 3) == TRUE
				|| over(game, &game->good_contact, E_MINE, 5) == TRUE)
			return (TRUE);
		if (game->nearest_adv.x > game->board.size.x / 2)
		{
			if (delta(&game->contact, &game->angle_opmine)
					<= delta(&game->good_contact, &game->angle_opmine))
				return (TRUE);
		}
		else
		{
			if (delta(&game->contact, &game->angle_opmine)
					< delta(&game->good_contact, &game->angle_opmine))
				return (TRUE);
		}
	}
	return (FALSE);
}

unsigned char	angle_opadv_mode(t_game *game)
{
	if (over(game, &game->contact, E_ADV, 3) == FALSE
			&& over(game, &game->contact, E_MINE, 5) == FALSE)
	{
		if (over(game, &game->good_contact, E_ADV, 3) == TRUE
				|| over(game, &game->good_contact, E_MINE, 5) == TRUE)
			return (TRUE);
		if (game->nearest_adv.x > game->board.size.x / 2)
		{
			if (delta(&game->contact, &game->angle_opadv)
					<= delta(&game->good_contact, &game->angle_opadv))
				return (TRUE);
		}
		else
		{
			if (delta(&game->contact, &game->angle_opadv)
					< delta(&game->good_contact, &game->angle_opadv))
				return (TRUE);
		}
	}
	return (FALSE);
}

unsigned char	glue_mode(t_game *game)
{
	if (game->nearest_adv.x > game->board.size.x / 2)
	{
		if (delta(&game->contact, &game->last_adv)
				<= delta(&game->good_contact, &game->last_adv))
			return (TRUE);
	}
	else if (delta(&game->contact, &game->last_adv)
			< delta(&game->good_contact, &game->last_adv))
		return (TRUE);
	return (FALSE);
}

unsigned char	attack_mode(t_game *game)
{
	if (game->nearest_adv.x > game->board.size.x / 2)
	{
		if (delta(&game->contact, &game->nearest_adv)
				<= delta(&game->good_contact, &game->nearest_adv))
			return (TRUE);
	}
	else if (delta(&game->contact, &game->nearest_adv)
			< delta(&game->good_contact, &game->nearest_adv))
		return (TRUE);
	return (FALSE);
}
