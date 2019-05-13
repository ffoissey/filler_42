/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharbon <lcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 05:04:20 by lcharbon          #+#    #+#             */
/*   Updated: 2017/10/31 00:38:36 by lcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "visual.h"
#include "mlx.h"
#define BUFF_SIZE 64

static int              ft_gnl_process(char *str, char **line, int r, char **st)
{
	int             i;
	int             tmp;

	i = 0;
	tmp = ft_strlen(str);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	str[i] = 0;
	*line = ft_strsub(str, 0, i);
	*st = ft_strsub(&str[i + 1], 0, tmp - i);
	if (str)
		ft_strdel(&str);
	if (r > 0)
		return (1);
	if (*st)
		ft_strdel(st);
	return (0);
}

static int              ft_get_stock(char **line, char **st)
{
	char                *tmp;
	int             i;

	tmp = *st;
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == 0)
		return (0);
	*line = ft_strndup(tmp, i);
	tmp[i] = 0;
	tmp = ft_strdup(&tmp[i + 1]);
	ft_strdel(st);
	*st = tmp;
	return (1);
}

int                 get_next_line(int fd, char **line)
{
	static char         *st = NULL;
	char                *buf;
	char                *str;
	int             r;

	if (st != NULL)
		if (ft_get_stock(line, &st) == 1)
			return (1);
	buf = ft_strnew(BUFF_SIZE);
	if (st)
		str = ft_strdup(st);
	else
		str = ft_strdup("");
	ft_strdel(&st);
	while ((r = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[r] = 0;
		str = ft_strjoindel(str, buf, 3);
		buf = ft_strnew(BUFF_SIZE);
		if (ft_strchr(str, '\n'))
			break;
	}
	if (buf)
		ft_strdel(&buf);
	if (r < 0)
		return (-1);
	return (ft_gnl_process(str, line, r, &st));
}

void				ft_fill_pixel(char *s, int y, int x, int col)
{
	int				pos;
	char			*des;

	pos = ((y * 1000) + x) * 4;
	s[pos] = col & 0xFF;
	s[pos + 1] = col >> 8 & 0xFF;
	s[pos + 2] = col >> 16;
}

int					ft_escape(t_gb *g)
{
	mlx_destroy_image(g->mlx, g->img);
	mlx_destroy_window(g->mlx, g->win);
	usleep(100000);
	write(1, "Leave\n", 6);
	exit (1);
	return (1);
}

int					ft_get_key(int keycode, t_gb *g)
{
	if (keycode == 53)
		ft_escape(g);
	return (1);
}

void				ft_init(t_gb *g)
{
	if (!(g->mlx = mlx_init()))
		ft_perror("Leave\n");
	if (!(g->win = mlx_new_window(g->mlx, 1000, 1000, "Filler Visual")))
		ft_perror("Leave\n");
	g->img = mlx_new_image(g->mlx, 1000, 1000);
	g->str_img = mlx_get_data_addr(g->img,
			&g->bpp, &g->s_l, &g->endn);
}

unsigned char		**ft_alloc_it(int n, char *line)
{
	unsigned char	**ret;
	int				a;
	int				nm;

	if (!(ret = (unsigned char**)malloc(sizeof(unsigned char*) * (n + 1))))
		return (NULL);
	a = 0;
	nm = n;
	while (n >= 0)
		ret[n--] = NULL;
	while (a < nm)
	{
		if (!(ret[a] = (unsigned char*)malloc(sizeof(unsigned char) * (strlen(line) + 1))))
			return (NULL);
		memset(ret[a], 0, sizeof(unsigned char) * strlen(line));
		a++;
	}
	return (ret);
}

void				ft_store_it(unsigned char **map, char *line, int n)
{
	int				i;
	int				a;

	a = 0;
	i = 0;
	while (line[i] != 0)
	{
		if (isalpha(line[i]) != 0 || line[i] == '.')
			map[n][a++] = line[i];
		i++;
	}
}

void				ft_fill_square(t_gb *g, int ym, int xm, unsigned char c, int sqlen, int sqlen_y)
{
	int				y;
	int				yl;
	int				x;
	int				xl;

	y = (ym * sqlen_y) - 1;
	yl = ((ym + 1) * sqlen_y);
	xl = ((xm + 1) * sqlen);
	while  (++y < yl - 1)
	{
		x = (xm * sqlen) - 1;
		while (++x < xl - 1)
		{
			if (c == 'O')
				ft_fill_pixel(g->str_img, y, x, 0xFF0000);
			else if (c == 'X')
				ft_fill_pixel(g->str_img, y, x, 0x00FFFF);
			else if (c == 'C')
				ft_fill_pixel(g->str_img, y, x, 0xFFFFFF);
			else if (c == 'D')
				ft_fill_pixel(g->str_img, y, x, 0x00FF00);
			else if (c == 'E')
				ft_fill_pixel(g->str_img, y, x, 0xFFFF00);
			else if (c == 'F')
				ft_fill_pixel(g->str_img, y, x, 0x2E0854);
			else if (c == 'M')
				ft_fill_pixel(g->str_img, y, x, 0xAAAAAA);
		}
	}
}

void				ft_draw_it(t_gb *g, unsigned char **map)
{
	int				y;
	int				x;
	int				xm;
	int				ym;
	int				sqlen;
	int				sqlen_y;

	xm = 0;
	ym = 0;
	while (map[0][xm] != 0)
		xm++;
	while (map[ym] != NULL)
		ym++;
	sqlen = 1000 / xm;
	sqlen_y = 1000 / (ym - 1);
	y = -1;
	while (map[++y] != NULL)
	{
		x = -1;
		while (map[y][++x] != 0)
			if (map[y][x] != '.')
				ft_fill_square(g, y, x, map[y][x], sqlen, sqlen_y);
	}
}

void				ft_free(unsigned char **map)
{
	int				a;

	a = 0;
	while (map[a] != NULL)
	{
		free(map[a]);
		map[a] = NULL;
		a++;
	}
	if (map)
		free(map);
	map = NULL;
}

int					ft_process(t_gb *g, char *line)
{
	unsigned char	**map;
	char			*line2;
	int				n_line;
	int				a;

	if (strstr(line, "Plateau"))
	{
		a = 0;
		n_line = atoi(&line[8]);
		ft_memdel((void**)&line);
		get_next_line(0, &line);
		ft_memdel((void**)&line);
		line2 = NULL;
		while (n_line > 0 && get_next_line(0, &line2))
		{
			if (a == 0)
				map = ft_alloc_it(n_line + 1, line2);
			ft_store_it(map, line2, a++);
			ft_memdel((void**)&line2);
			n_line--;
		}
		ft_memdel((void**)&line2);
		ft_draw_it(g, map);
		ft_free(map);
		mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
		write(1, "OK\n", 3);
	}
	ft_memdel((void**)&line);
	return (1);
}

int					ft_preprocess(t_gb *g)
{
	char			*line;

	if (get_next_line(0, &line))
		return (ft_process(g, line));
	return (0);
}

int					main(void)
{
	t_gb			*g;
	int				loop;
	char			*line;

	loop = 1;
	line = NULL;
	if (!(g = (t_gb*)malloc(sizeof(t_gb))))
		ft_perror("Can't allocate memory");
	memset(g, 0, sizeof(t_gb));
	ft_init(g);
	mlx_key_hook(g->win, ft_get_key, g);
	mlx_hook(g->win, 17, 0, ft_escape, g);
	mlx_loop_hook(g->mlx, ft_preprocess, g);
	mlx_loop(g->mlx);
	return (1);
}
