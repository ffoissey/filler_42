#include "filler.h"

unsigned char	angle_mode(t_game *game, t_point *start)
{
	if ((get_delta(start, &game->angle)
		< get_delta(&game->to_play, &game->angle)
		|| (get_delta(start, &game->angle)
			== get_delta(&game->to_play, &game->angle)
		&& get_delta(start, &game->last_adv)
		< get_delta(&game->to_play, &game->last_adv))))
		return (TRUE);
	return (FALSE);
}

unsigned char	spider_y_mode(t_game *game, t_point *start)
{
	if ((game->board.size.x - start->x <= game->board.size.x - game->to_play.x
		|| start->x < game->to_play.x)
		&& get_delta(start, &game->last_adv)
		<= get_delta(&game->to_play, &game->last_adv))
		return (TRUE);
	return (FALSE);
}

unsigned char	spider_x_mode(t_game *game, t_point *start)
{
	if ((game->board.size.y - start->y <= game->board.size.y - game->to_play.y
		|| start->y < game->to_play.y)
		&& get_delta(start, &game->last_adv)
		<= get_delta(&game->to_play, &game->last_adv))
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
	if (game->last_mine.x != 0 && game->last_mine.y != 0
		&& game->last_adv.x == 0 && game->last_adv.y == 0)
		game->mode = E_EXPANSION; 
	else if (get_delta(&game->last_mine, &game->angle)
			> get_delta(&game->last_mine, &game->last_adv)
			&& scanner(game, &game->angle, E_MINE, 3) == FALSE
			&& scanner(game, &game->last_adv, E_MINE, 5) == FALSE)
		game->mode = E_ANGLE; 
	else if (get_delta(&game->last_mine, &game->core_adv)
			> get_delta(&game->last_mine, &game->last_adv)
			&& scanner(game, &game->last_adv, E_MINE, 5) == FALSE)
		game->mode = E_CORE; 
	else if (scanner(game, &game->last_adv, E_MINE, 3) == TRUE)
		game->mode = E_ATTACK; 
	else if ((game->board.size.x - game->last_adv.x <= 10
				&& game->board.size.x - game->last_adv.x > 0)
		|| (game->last_adv.x > 0 && game->last_adv.x <= 10))
		game->mode = E_SPIDER_Y; 
	else if ((game->board.size.y - game->last_adv.y <= 10
				&& game->board.size.y - game->last_adv.y > 0)
		|| (game->last_adv.y > 0 && game->last_adv.y <= 10))
		game->mode = E_SPIDER_X; 
}

void	print_strategy(t_game *game)
{
	if (game->mode == E_ANGLE)
		ft_dprintf(2, "\033[34mAngle\033[0m\n");
	else if (game->mode == E_ATTACK)
		ft_dprintf(2, "\033[31mAttack\033[0m\n");
	else if (game->mode == E_SPIDER_X)
		ft_dprintf(2, "\033[33mSpider X\033[0m\n");
	else if (game->mode == E_SPIDER_Y)
		ft_dprintf(2, "\033[36mSpider Y\033[0m\n");
	else if (game->mode == E_CORE)
		ft_dprintf(2, "\033[35mCore\033[0m\n");
	else if (game->mode == E_EXPANSION)
		ft_dprintf(2, "\033[32mExpansion\033[0m\n");
}
