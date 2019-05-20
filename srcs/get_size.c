/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:31:30 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/18 18:31:38 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static unsigned char	check_size_format(char *line, t_point *size)
{
	unsigned char count;

	count = 0;
	while (*line != '\0' && *line != ':')
	{
		if (*line != ' ' || count >= 2)
			return (FALSE);
		line++;
		if (count == 0)
			size->x = ft_atoi(line);
		else
			size->y = ft_atoi(line);
		while (ft_isdigit(*line) == TRUE)
			line++;
		count++;
	}
	return (*line == ':' && *(line + 1) == '\0');
}

static int				alloc_game(enum e_state ***mx, t_point *size)
{
	int		i;

	i = 0;
	*mx = (enum e_state **)malloc(sizeof(enum e_state *) * size->x);
	if (*mx == NULL)
		return (FAILURE);
	while (i < size->x)
	{
		(*mx)[i] = (enum e_state *)malloc(sizeof(enum e_state) * size->y);
		if ((*mx)[i] == NULL)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int						process_size(t_point *game_size, enum e_state ***mx,
								char *line, char *type)
{
	t_point		size;
	int			len;

	ft_bzero(&size, sizeof(t_point));
	len = ft_strlen(type);
	if (ft_strnequ(line, type, len) == FALSE)
		return (FAILURE);
	line += len;
	if (check_size_format(line, &size) == FALSE)
		return (FAILURE);
	if (size.x == 0 || size.y == 0)
		return (FAILURE);
	if (game_size->x == 0 && game_size->y == 0)
	{
		game_size->x = size.x;
		game_size->y = size.y;
		if (*mx == NULL && alloc_game(mx, &size) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
