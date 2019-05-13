/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharbon <lcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 00:10:58 by lcharbon          #+#    #+#             */
/*   Updated: 2017/10/13 07:57:58 by lcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>


typedef struct		s_gb
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*str_img;
	int				bpp;
	int				s_l;
	int				endn;
}					t_gb;

#endif
