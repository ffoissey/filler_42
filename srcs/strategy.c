#include "filler.h"

unsigned char	angle_target_mode(t_game *game)
{
	if (over(game, &game->contact, E_ADV, 5) == FALSE
		&& over(game, &game->contact, E_MINE, 5) == FALSE)
	{
		if (over(game, &game->good_contact, E_ADV, 5) == TRUE
			|| over(game, &game->good_contact, E_MINE, 5) == TRUE)
			return (TRUE);
		if (get_delta(&game->contact, &game->angle_target)
			< get_delta(&game->to_play, &game->angle_target))
			return (TRUE);
	}
	return (FALSE);
}
unsigned char	angle_opmine_mode(t_game *game)
{
	if (over(game, &game->contact, E_ADV, 5) == FALSE
	   && over(game, &game->contact, E_MINE, 5) == FALSE)
	{
		if (over(game, &game->good_contact, E_ADV, 5) == TRUE
			|| over(game, &game->good_contact, E_MINE, 5) == TRUE)
			return (TRUE);
		if (get_delta(&game->contact, &game->angle_opmine)
			<= get_delta(&game->good_contact, &game->angle_opmine))
			return (TRUE);
	}
	return (FALSE);
}
unsigned char	angle_opadv_mode(t_game *game)
{
	if (over(game, &game->contact, E_ADV, 5) == FALSE
		&& over(game, &game->contact, E_MINE, 5) == FALSE)
	{
		if (over(game, &game->good_contact, E_ADV, 5) == TRUE
			|| over(game, &game->good_contact, E_MINE, 5) == TRUE)
			return (TRUE);
		if (get_delta(&game->contact, &game->angle_opadv)
			<= get_delta(&game->good_contact, &game->angle_opadv))
			return (TRUE);
	}
	return (FALSE);
}

unsigned char	glue_mode(t_game *game)
{
	if (get_delta(&game->contact, &game->last_adv)
		<= get_delta(&game->good_contact, &game->last_adv))
		return (TRUE);
	return (FALSE);
}

unsigned char	attack_mode(t_game *game)
{
	if (get_delta(&game->contact, &game->nearest_adv)
		<= get_delta(&game->good_contact, &game->nearest_adv)
	   //&& over(game, &game->contact, E_MINE, 1) == FALSE)
	   && over(game, &game->contact, E_EMPTY, 1) == TRUE)
		return (TRUE);
	return (FALSE);
}

void	select_strategy(t_game *game)
{
	if (((scanner(game, &game->last_adv, E_MINE, 2) == TRUE)
		|| (get_delta(&game->angle_mine, &game->last_adv)
			< get_delta(&game->angle_mine, &game->last_mine)))
		&& over(game, &game->last_adv, E_MINE, 2) == FALSE
		&& over(game, &game->last_adv, E_EMPTY, 3) == TRUE)
		game->mode = E_GLUE;
	else if (game->close_angle_target == FALSE
			&& game->better_angle == E_ANGLE_TARGET
			&& over(game, &game->angle_target, E_MINE, 2) == FALSE
			&& scanner(game, &game->angle_target, E_ADV, 1) == FALSE
				&& over(game, &game->angle_target, E_EMPTY, 5) == TRUE)
		game->mode = E_ANGLE_TARGET; 
	else if (game->close_angle_opmine == FALSE
			&& game->better_angle == E_ANGLE_OPMINE
			&& over(game, &game->angle_target, E_MINE, 2) == FALSE
			&& scanner(game, &game->angle_opmine, E_MINE, 1) == FALSE
			&& scanner(game, &game->angle_opmine, E_ADV, 1) == FALSE
					&& over(game, &game->angle_opmine, E_EMPTY, 5) == TRUE)
		game->mode = E_ANGLE_OPMINE; 

	else if (game->close_angle_opadv == FALSE
			&& game->better_angle == E_ANGLE_OPADV
			&& over(game, &game->angle_target, E_MINE, 2) == FALSE
			&& scanner(game, &game->angle_opadv, E_MINE, 1) == FALSE
			&& scanner(game, &game->angle_opadv, E_ADV, 1) == FALSE
						&& over(game, &game->angle_opadv, E_EMPTY, 5) == TRUE)
		game->mode = E_ANGLE_OPADV; 
	else if (get_delta(&game->last_mine, &game->nearest_adv) > 100 &&
			scanner(game, &game->nearest_adv, E_MINE, 5) == FALSE)
			 		game->mode = E_ATTACK;
	else if ((over(game, &game->last_adv, E_EMPTY, 2) == TRUE))
		game->mode = E_GLUE;
	else
		game->mode = E_ATTACK;
}

void	print_strategy(t_game *game)
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
