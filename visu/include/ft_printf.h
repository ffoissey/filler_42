/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 13:38:46 by lcharbon          #+#    #+#             */
/*   Updated: 2017/08/21 19:01:02 by lcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <wchar.h>
# include <fcntl.h>
# include "libft.h"
# define PF_BUFF_SIZE 15

typedef struct	s_float
{
	long		t1;
	long		t2;
	double		tmp;
	char		*mantisse;
	int			e;
}				t_float;

typedef struct	s_data
{
	char		buf[4096];
	int			nbuf;
	int			data[15];
	char		conv;
	int			n_char;
	int			fd;
	int			opfd;
}				t_data;

int				ft_printf(char const *format, ...);
void			ftpf_get_data(const char **format, t_data *data, va_list ap);
void			ftpf_get_prec(char const **format, t_data *data, va_list ap);
void			ftpf_get_width(char const **format, t_data *data, va_list ap);
void			ftpf_get_modifier(char const **format, t_data *data);
void			ftpf_get_flags(char const **format, t_data *data);
void			ftpf_get_special(char const **format, t_data *data, va_list ap);
void			ftpf_get_conv(char const **format, t_data *data);

int				ftpf_flags(char c);
int				ftpf_modifier(char c);
int				ft_count_ch_int(intmax_t nb);
int				ftpf_convert(t_data *data, va_list ap);

intmax_t		ftpf_valist_sign(t_data *data, va_list ap, char c);
uintmax_t		ftpf_valist_unsign(t_data *data, va_list ap, char c);
char			*ftpf_valist_strings(t_data *data, va_list ap);
void			ftpf_valist_char(t_data *data, va_list ap, char *ret);

int				ftpf_n_conv(t_data *data, va_list ap);
int				ftpf_ch_conv(t_data *data, va_list ap);
int				ftpf_expo_conv(t_data *data, va_list ap);
int				ftpf_gep_conv(t_data *data, va_list ap);
int				ftpf_iso_conv(t_data *data, va_list ap);
int				ftpf_float_conv(t_data *data, va_list ap);
int				ftpf_hexafloat_conv(t_data *data, va_list ap);
int				ftpf_strings_conv(t_data *data, va_list ap);
int				ftpf_unsign_p_conv(t_data *data, va_list ap);
int				ftpf_sign_conv(t_data *data, va_list ap, char c);
int				ftpf_unsign_conv(t_data *data, va_list ap, char c);

void			ftpf_upcase(char *str);
char			*ftpf_sign_itoa(long long n);
void			ftpf_apo_flag(char **str, t_data *data);
char			*ftpf_uitoa_base(unsigned long n, char c);
char			*ftpf_float_itoa(double n, int pre, int x);
char			*ftpf_expo_itoa(double n, int pre, int over_pre);
char			*ftpf_gep_itoa(double n, int pre, int over_pre);
void			ftpf_unsign_zero(t_data *data, char **str, uintmax_t arg);

void			ftpf_expo_pre(char **str, long double arg, int pre);
int				ftpf_expo_cal_pre(t_data *data);
void			ft_reverse_str(char *str);

#endif
