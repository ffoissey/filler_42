/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 07:54:59 by lcharbon          #+#    #+#             */
/*   Updated: 2017/10/31 00:08:16 by lcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# define MAX_FD 10240

typedef struct	s_gnl
{
	char	*buf;
	char	*str;
	char	*tmp;
	int		read_ret;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif
