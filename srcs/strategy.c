#include "filler.h"

unsigned char	conquest_mode(t_game *game, t_point *start)
{
	(void)start;
	if (get_delta(&game->contact, &game->nearest_adv)
		> get_delta(&game->good_contact, &game->nearest_adv)
		&& over(game, &game->contact, E_MINE, 5, 0.7) == FALSE)
		return (TRUE);
	return (FALSE);
}

unsigned char	angle_target_mode(t_game *game, t_point *start)
{
	(void)start;
	if (over(game, start, E_ADV, 5, 0.5) == FALSE
		&& over(game, start, E_MINE, 5, 0.5) == FALSE)
	{
		if (over(game, &game->good_contact, E_ADV, 5, 0.5) == TRUE
			|| over(game, &game->good_contact, E_MINE, 5, 0.5) == TRUE)
			return (TRUE);
		if (get_delta(start, &game->angle_target)
			< get_delta(&game->to_play, &game->angle_target))
			return (TRUE);
	}
	return (FALSE);
}
unsigned char	angle_opmine_mode(t_game *game, t_point *start)
{
	(void)start;
	if (over(game, &game->contact, E_ADV, 5, 0.7) == FALSE
	   && over(game, &game->contact, E_MINE, 5, 0.7) == FALSE)
	{
		if (over(game, &game->good_contact, E_ADV, 5, 0.7) == TRUE
			|| over(game, &game->good_contact, E_MINE, 5, 0.7) == TRUE)
			return (TRUE);
		if (get_delta(&game->contact, &game->angle_opmine)
			<= get_delta(&game->good_contact, &game->angle_opmine))
			return (TRUE);
	}
	return (FALSE);
}
unsigned char	angle_opadv_mode(t_game *game, t_point *start)
{
	(void)start;
	if (over(game, &game->contact, E_ADV, 5, 0.7) == FALSE
		&& over(game, &game->contact, E_MINE, 5, 0.7) == FALSE)
	{
		if (over(game, &game->good_contact, E_ADV, 5, 0.7) == TRUE
			|| over(game, &game->good_contact, E_MINE, 5, 0.7) == TRUE)
			return (TRUE);
		if (get_delta(&game->contact, &game->angle_opadv)
			<= get_delta(&game->good_contact, &game->angle_opadv))
			return (TRUE);
	}
	return (FALSE);
}

unsigned char	spider_x_down_mode(t_game *game, t_point *start)
{
	(void)start;
	if (get_delta(&game->contact, &game->nearest_adv)
		<= get_delta(&game->good_contact, &game->nearest_adv))
		return (TRUE);
	return (FALSE);
}

unsigned char	spider_x_up_mode(t_game *game, t_point *start)
{
	(void)start;
	if (game->contact.x < game->good_contact.x)
		return (TRUE);
	return (FALSE);
}

unsigned char	spider_y_right_mode(t_game *game, t_point *start)
{
	(void)start;
	if (get_delta(&game->contact, &game->nearest_adv)
		< get_delta(&game->good_contact, &game->nearest_adv))
		return (TRUE);
	return (FALSE);
}

unsigned char	spider_y_left_mode(t_game *game, t_point *start)
{
	(void)start;
	if (game->contact.y <= game->good_contact.y)
		return (TRUE);
	return (FALSE);
}

unsigned char	glue_mode(t_game *game, t_point *start)
{
	(void)start;
	if (get_delta(&game->contact, &game->last_adv)
		<= get_delta(&game->good_contact, &game->last_adv))
		return (TRUE);
	return (FALSE);
}

unsigned char	attack_mode(t_game *game, t_point *start)
{
	(void)start;
	if (get_delta(&game->contact, &game->nearest_adv)
		<= get_delta(&game->good_contact, &game->nearest_adv)
	   //&& over(game, start, E_MINE, 1, 0.7) == FALSE)
	   && over(game, start, E_EMPTY, 1, 0.7) == TRUE)
		return (TRUE);
	return (FALSE);
}

unsigned char	core_mode(t_game *game, t_point *start)
{
	(void)start;
	if (get_delta(&game->contact, &game->core_adv)
		< get_delta(&game->good_contact, &game->core_adv))
		return (TRUE);
	return (FALSE);
}

unsigned char	expansion_mode(t_game *game, t_point *start)
{
	(void)start;
	if (get_delta(&game->contact, &game->core_adv)
		> get_delta(&game->good_contact, &game->core_adv))
		return (TRUE);
	return (FALSE);
}

void	select_strategy(t_game *game)
{
/*	if (game->last_mine.y >= 0 && game->last_mine.y < 3
			&& game->left_close % 2 == 0)
	{
		game->left_close++;
		game->mode = E_SPIDER_Y_LEFT; 
	}
	
	else if (game->board.size.y - game->last_mine.y < 3
			&& game->board.size.y - game->last_mine.y >= 0
			&& game->right_close % 2 == 0)
	{
		game->right_close++;
		game->mode = E_SPIDER_Y_RIGHT;
	}

	else if (game->last_mine.x >= 0 && game->last_mine.x < 3
			&& game->up_close % 2 == 0)
	{
		game->up_close++;
		game->mode = E_SPIDER_X_UP; 
	}

	else if (game->board.size.x - game->last_mine.x < 3
			&& game->board.size.x - game->last_mine.x >= 0
			&& game->down_close % 2 == 0)
	{
		game->down_close++;
		game->mode = E_SPIDER_X_DOWN;
	}
	else*/ if (((scanner(game, &game->last_adv, E_MINE, 2) == TRUE)
		|| (get_delta(&game->angle_mine, &game->last_adv)
			< get_delta(&game->angle_mine, &game->last_mine)))
		&& over(game, &game->last_adv, E_MINE, 2, 0.7) == FALSE
		&& over(game, &game->last_adv, E_EMPTY, 3, 0.7) == TRUE)
		game->mode = E_GLUE;
	else if (game->close_angle_target == FALSE
			&& game->better_angle == E_ANGLE_TARGET
			&& over(game, &game->angle_target, E_MINE, 2, 0.7) == FALSE
			&& scanner(game, &game->angle_target, E_ADV, 1) == FALSE
				&& over(game, &game->angle_target, E_EMPTY, 5, 0.7) == TRUE)
		game->mode = E_ANGLE_TARGET; 
	else if (game->close_angle_opmine == FALSE
			&& game->better_angle == E_ANGLE_OPMINE
			&& over(game, &game->angle_target, E_MINE, 2, 0.7) == FALSE
			&& scanner(game, &game->angle_opmine, E_MINE, 1) == FALSE
			&& scanner(game, &game->angle_opmine, E_ADV, 1) == FALSE
					&& over(game, &game->angle_opmine, E_EMPTY, 5, 0.7) == TRUE)
		game->mode = E_ANGLE_OPMINE; 

	else if (game->close_angle_opadv == FALSE
			&& game->better_angle == E_ANGLE_OPADV
			&& over(game, &game->angle_target, E_MINE, 2, 0.7) == FALSE
			&& scanner(game, &game->angle_opadv, E_MINE, 1) == FALSE
			&& scanner(game, &game->angle_opadv, E_ADV, 1) == FALSE
						&& over(game, &game->angle_opadv, E_EMPTY, 5, 0.7) == TRUE)
		game->mode = E_ANGLE_OPADV; 
	else if (get_delta(&game->last_mine, &game->nearest_adv) > 100 &&
			scanner(game, &game->nearest_adv, E_MINE, 5) == FALSE)
			 		game->mode = E_ATTACK;
	//else if ((scanner(game, &game->last_adv, E_, 2) == TRUE))
	else if ((over(game, &game->last_adv, E_EMPTY, 2, 0.5) == TRUE))
		game->mode = E_GLUE;
	else
		game->mode = E_ATTACK;
}

void	print_strategy(t_game *game)
{
	if (game->mode == E_ANGLE_TARGET)
		ft_dprintf(2, "\033[34mAngle TARGET\033[0m\n");
	else if (game->mode == E_ANGLE_OPMINE)
		ft_dprintf(2, "\033[34mAngle OPMINE\033[0m\n");
	else if (game->mode == E_ANGLE_OPADV)
		ft_dprintf(2, "\033[34mAngle OPADV\033[0m\n");
	else if (game->mode == E_ATTACK)
		ft_dprintf(2, "\033[31mAttack\033[0m\n");
	else if (game->mode == E_SPIDER_X_UP)
		ft_dprintf(2, "\033[33mSpider X UP\033[0m\n");
	else if (game->mode == E_SPIDER_X_DOWN)
		ft_dprintf(2, "\033[33mSpider X DOWN\033[0m\n");
	else if (game->mode == E_SPIDER_Y_LEFT)
		ft_dprintf(2, "\033[36mSpider Y LEFT\033[0m\n");
	else if (game->mode == E_SPIDER_Y_RIGHT)
		ft_dprintf(2, "\033[36mSpider Y RIGHT\033[0m\n");
	else if (game->mode == E_CORE)
		ft_dprintf(2, "\033[35mCore\033[0m\n");
	else if (game->mode == E_EXPANSION)
		ft_dprintf(2, "\033[32mExpansion\033[0m\n");
	else if (game->mode == E_CONQUEST)
		ft_dprintf(2, "\033[37mConquest\033[0m\n");
	else if (game->mode == E_GLUE)
		ft_dprintf(2, "\033[38mGlue\033[0m\n");
//	ft_dprintf(2, "NEAREST: x %d, y %d\n", game->nearest_adv.x, game->nearest_adv.y);
//	ft_dprintf(2, "ANGLE TARGET: x %d, y %d\n", game->angle_target.x, game->angle_target.y);
//	ft_dprintf(2, "ANGLE ADV: x %d, y %d\n", game->angle_adv.x, game->angle_adv.y);
//	ft_dprintf(2, "ANGLE MINE: x %d, y %d\n", game->angle_mine.x, game->angle_mine.y);
//	ft_dprintf(2, "ANGLE OPMINE: x %d, y %d\n", game->angle_opmine.x, game->angle_opmine.y);
//	ft_dprintf(2, "ANGLE OPADV: x %d, y %d\n", game->angle_opadv.x, game->angle_opadv.y);
//	ft_dprintf(2, "CORE ADV: x %d, y %d\n", game->core_adv.x, game->core_adv.y);
//	ft_dprintf(2, "CORE MINE: x %d, y %d\n", game->core_mine.x, game->core_mine.y);
}
