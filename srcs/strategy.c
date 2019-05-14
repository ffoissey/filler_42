#include "filler.h"

unsigned char	angle_mode(t_game *game, t_point *start)
{
	if (get_delta(start, &game->angle)
		< get_delta(&game->to_play, &game->angle))
		return (TRUE);
	return (FALSE);
}

unsigned char	spider_x_down_mode(t_game *game, t_point *start)
{
	if (game->board.size.x - start->x < game->board.size.x - game->to_play.x)
		return (TRUE);
	return (FALSE);
}

unsigned char	spider_x_up_mode(t_game *game, t_point *start)
{
	if (start->x < game->to_play.x)
		return (TRUE);
	return (FALSE);
}

unsigned char	spider_y_right_mode(t_game *game, t_point *start)
{
	if (game->board.size.y - start->y < game->board.size.y - game->to_play.y)
		return (TRUE);
	return (FALSE);
}

unsigned char	spider_y_left_mode(t_game *game, t_point *start)
{
	if (start->y < game->to_play.y)
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
	else if (get_delta(&game->last_mine, &game->last_adv) > 20
			|| scanner(game, &game->last_adv, E_MINE, 3) == FALSE)
		game->mode = E_ATTACK; 
	else if (get_delta(&game->last_mine, &game->angle)
			> get_delta(&game->last_adv, &game->angle)
			&& scanner(game, &game->angle, E_MINE, 3) == FALSE)
		game->mode = E_ANGLE; 
	else if (get_delta(&game->last_mine, &game->core_adv)
			> get_delta(&game->last_mine, &game->last_adv)
			&& get_delta(&game->last_mine, &game->last_adv) > 20)
		game->mode = E_CORE; 
	else if (game->last_adv.y > 2 && game->last_adv.y < 6)
		game->mode = E_SPIDER_Y_LEFT; 
	else if (game->board.size.y - game->last_adv.y < 6
			&& game->board.size.y - game->last_adv.y > 2)
		game->mode = E_SPIDER_Y_RIGHT;
	else if (game->last_adv.x > 2 && game->last_adv.x < 6)
		game->mode = E_SPIDER_X_UP; 
	else if (game->board.size.x - game->last_adv.x < 6
			&& game->board.size.x - game->last_adv.x > 2)
		game->mode = E_SPIDER_X_DOWN;
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
}
