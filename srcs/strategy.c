#include "filler.h"

unsigned char	conquest_mode(t_game *game, t_point *start)
{
	if (get_delta(start, &game->last_mine)
		> get_delta(&game->to_play, &game->last_mine))
		return (TRUE);
	return (FALSE);
}

unsigned char	angle_mode(t_game *game, t_point *start)
{
	if (get_delta(start, &game->angle_target)
		< get_delta(&game->to_play, &game->angle_target))
		return (TRUE);
	return (FALSE);
}

unsigned char	spider_x_down_mode(t_game *game, t_point *start)
{
	if (get_delta(start, &game->nearest_adv)
		< get_delta(&game->to_play, &game->nearest_adv))
		return (TRUE);
	return (FALSE);
}

unsigned char	spider_x_up_mode(t_game *game, t_point *start)
{
	if (get_delta(start, &game->nearest_adv)
		< get_delta(&game->to_play, &game->nearest_adv))
		return (TRUE);
	return (FALSE);
}

unsigned char	spider_y_right_mode(t_game *game, t_point *start)
{
	if (get_delta(start, &game->nearest_adv)
		< get_delta(&game->to_play, &game->nearest_adv))
		return (TRUE);
	return (FALSE);
}

unsigned char	spider_y_left_mode(t_game *game, t_point *start)
{
	if (start->y < game->contact.y)
		return (TRUE);
	return (FALSE);
}

unsigned char	attack_mode(t_game *game, t_point *start)
{
	if (get_delta(start, &game->last_adv)
		< get_delta(&game->to_play, &game->last_adv))
		return (TRUE);
	return (FALSE);
}

unsigned char	core_mode(t_game *game, t_point *start)
{
	if (get_delta(start, &game->core_adv)
		< get_delta(&game->to_play, &game->core_adv))
		return (TRUE);
	return (FALSE);
}

unsigned char	expansion_mode(t_game *game, t_point *start)
{
	if (get_delta(start, &game->core_adv)
		> get_delta(&game->to_play, &game->core_adv))
		return (TRUE);
	return (FALSE);
}

void	select_strategy(t_game *game)
{
	if (game->last_adv.x == 0 && game->last_adv.y == 0)
		game->mode = E_EXPANSION; 


	else if (get_delta(&game->core_adv, &game->angle_target)
			< get_delta(&game->last_mine, &game->angle_target)
			&& scanner(game, &game->core_adv, E_EMPTY, 2) == TRUE
			&& game->get_angle == 0)
		game->mode = E_ANGLE; 

	else if (get_delta(&game->last_mine, &game->last_adv) > 10)
		game->mode = E_ATTACK; 

	else if (get_delta(&game->last_mine, &game->core_adv)
			> get_delta(&game->last_mine, &game->last_adv)
			&& get_delta(&game->last_mine, &game->last_adv) > 20
			&& scanner(game, &game->core_adv, E_MINE, 3) == FALSE)
		game->mode = E_CORE; 

	else if (game->last_adv.y >= 0 && game->last_adv.y < 5)
		game->mode = E_SPIDER_Y_LEFT; 
	
	else if (game->board.size.y - game->last_adv.y < 5 
			&& game->board.size.y - game->last_adv.y >= 0)
		game->mode = E_SPIDER_Y_RIGHT;

	else if (game->last_adv.x >= 0 && game->last_adv.x < 5)
		game->mode = E_SPIDER_X_UP; 

	else if (game->board.size.x - game->last_adv.x < 5
			&& game->board.size.x - game->last_adv.x >= 0)
		game->mode = E_SPIDER_X_DOWN;

	else
		game->mode = E_CONQUEST;
}

void	print_strategy(t_game *game)
{
	if (game->mode == E_ANGLE)
		ft_dprintf(2, "\033[34mAngle\033[0m\n");
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
	ft_dprintf(2, "x %d, y %d\n", game->nearest_adv.x, game->nearest_adv.y);
	ft_dprintf(2, "ANGLE: x %d, y %d\n", game->angle_target.x, game->angle_target.y);
	ft_dprintf(2, "ANGLE ADV: x %d, y %d\n", game->angle_adv.x, game->angle_adv.y);
	ft_dprintf(2, "ANGLE MINE: x %d, y %d\n", game->angle_mine.x, game->angle_mine.y);
	ft_dprintf(2, "CORE ADV: x %d, y %d\n", game->core_adv.x, game->core_adv.y);
	ft_dprintf(2, "CORE MINE: x %d, y %d\n", game->core_mine.x, game->core_mine.y);
}
