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

int					get_size(t_point *game_size, char *line, char *type)
{
	t_point		size;
	size_t		len;

	bzero(&size, sizeof(t_point));
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
	}
	else if (size.x != game_size->x || size.y != game_size->y)
		return (FAILURE);
	return (SUCCESS);
}
