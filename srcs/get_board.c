#include "filler.h"

unsigned char	check_first_line_board(unsigned int row, char *line)
{
	size_t	i;
	size_t	max;
	size_t	count;

	i = 0;
	max = row + 4;
	if (ft_strlen(line) != max)
		return (FALSE);
	while (i < 4)
	{
		if (line[i] != ' ')
			return (FALSE);
		i++;
	}
	count = 0;
	while (i < max)
	{
		if (count % 10 + '0' != line[i])
			return (FALSE);
		count++;
		i++;
	}
	return (TRUE);
}
