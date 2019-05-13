/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 16:16:52 by lcharbon          #+#    #+#             */
/*   Updated: 2017/09/13 17:23:45 by lcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_line_reader(int fd, char **line);
void				ft_test_memory(void);

void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstadd(t_list **alst, t_list *new);

int					ft_max(int n1, int n2);
int					ft_min(int n1, int n2);
int					ft_abs(int n);
int					ft_atoi(const char *str);
int					ft_atoidel(char *str);
unsigned long		ft_uatoi(const char *str);
long				ft_latoi(const char *str);
int					ft_count_c_int(long long n);
int					ft_ucount_c_int(unsigned long n);
char				*ft_itoa(long long n);
char				*ft_uitoa(unsigned long n);
char				*ft_itoa_base(long n, int base);
char				*ft_uitoa_base(unsigned long n, int base);
char				*ft_ftoa(double n, int pre);
int					ft_power(int n, int p);
unsigned long		ft_upower(unsigned long n, int p);

void				ft_bzero(void *s, size_t n);
void				ft_memdel(void **ap);
void				*ft_memalloc(size_t size);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memset(void	*b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst,
					const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);

int					ft_strlen(const char *s);
int					ft_wstrlen(wchar_t *str);
char				*ft_strnew(size_t size);
char				*ft_strnewch(size_t size, char c);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, int n);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strchr(const char *s, int c);
int					ft_istrchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big,
					const char *little, size_t len);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strsubdel(char *s, unsigned int start, int len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoindel(char *s1, char *s2, int i);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
void				ft_str_up(char *str);
char				*ft_str_add_ch(char *str, char c);
char				*ft_str_insert(char *s1, char *s2, int n);
void				ft_str_remplace(char *str, char c1, char c2);

int					ft_printf(const char *restrict format, ...);
void				ft_perror(char *error);
void				ft_perrorn(char *error);
void				ft_putchar(char c);
void				ft_putstr(char *str);
void				ft_putendl(char const *s);
void				ft_putnbr(long long n);
void				ft_putnbrendl(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

int					ft_putchar_extend(wchar_t c);
int					ft_putstr_extend(wchar_t *str);
char				*ft_putaddr(void *s);

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isalnum(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isspace(unsigned char c);
int					ft_issign(int c);

#endif
