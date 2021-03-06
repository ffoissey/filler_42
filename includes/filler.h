/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:23:20 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/21 12:48:25 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

# define PLAYER_ONE 	"$$$ exec p1 : ["
# define PLAYER_TWO 	"$$$ exec p2 : ["
# define PLAYER_SIZE 	15
# define EMPTY			'.'
# define FULL			'*'
# define P1_CHAR		'O'
# define P1_LAST_CHAR	'o'
# define P2_CHAR		'X'
# define P2_LAST_CHAR	'x'
# define PLATEAU		"Plateau"
# define PIECE			"Piece"

enum					e_action
{
	E_GET_PLAYER,
	E_GET_BOARD_SIZE,
	E_GET_BOARD_FIRST_LINE,
	E_GET_BOARD,
	E_GET_PIECE_SIZE,
	E_GET_PIECE,
	E_SPEAK,
	E_ERROR,
	E_WAIT
};

enum					e_state
{
	E_EMPTY,
	E_ADV,
	E_LAST_ADV,
	E_MINE,
	E_LAST_MINE,
	E_FULL,
	E_UNKNOW
};

enum					e_mode
{
	E_ANGLE_TARGET,
	E_ANGLE_OPMINE,
	E_ANGLE_OPADV,
	E_ATTACK,
	E_GLUE,
	E_NO_ANGLE
};

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_mx
{
	t_point				size;
	enum e_state		**mx;
}						t_mx;

typedef	struct			s_game
{
	char				*process_name;
	t_mx				board;
	t_mx				piece;
	enum e_action		action;
	enum e_mode			mode;
	int					row;
	char				adv_char;
	char				adv_last_char;
	char				my_char;
	char				my_last_char;
	t_point				last_adv;
	t_point				nearest_adv;
	t_point				last_mine;
	t_point				core_adv;
	t_point				core_mine;
	t_point				angle_target;
	t_point				angle_adv;
	t_point				angle_mine;
	t_point				angle_opmine;
	t_point				angle_opadv;
	enum e_mode			better_angle;
	t_point				contact;
	t_point				good_contact;
	t_point				to_play;
	int					turn;
	int					error;
}						t_game;

typedef void			(*t_process)(t_game *, char **);
typedef unsigned char	(*t_strategy)(t_game *);

/*
*** Action
*/

void					get_player(t_game *game, char **line);
void					get_board_first_line(t_game *game, char **line);
void					get_board(t_game *game, char **line);
void					get_size(t_game *game, char **line);
void					get_piece(t_game *game, char **line);

/*
*** Get Size
*/

int						process_size(t_point *game_size, enum e_state ***mx,
								char *line, char *type);

/*
*** Get Board
*/

unsigned char			check_first_line_board(unsigned int row, char *line);
int						get_line_board(t_game *game, char *line);
int						get_line_piece(t_game *game, char *line);

/*
*** Process
*/

void					ft_process(t_game *game);

/*
*** Select Strategy
*/

void					print_strategy(t_game *game);
void					select_strategy(t_game *game);

/*
*** Strategy
*/

unsigned char			angle_target_mode(t_game *game);
unsigned char			angle_opmine_mode(t_game *game);
unsigned char			angle_opadv_mode(t_game *game);
unsigned char			attack_mode(t_game *game);
unsigned char			glue_mode(t_game *game);

/*
*** Utils
*/

void					speak(t_game *game, char **line);
void					error(t_game *game, char **line);
void					free_matrix(t_mx *mx);
int						delta(t_point *a, t_point *b);
unsigned char			check_first_line_board(unsigned int row, char *line);

/*
*** Tools
*/

int						scanner(t_game *game, t_point *target,
							enum e_state state, int zone);
int						over(t_game *game, t_point *target,
							enum e_state state, int zone);
t_point					choose_angle(t_game *game, t_point *ref);
void					chose_better_angle(t_game *game);
void					get_angle(t_game *game);

/*
*** Tools2
*/

t_point					nearest(t_game *game);
int						get_better(t_game *game, t_point *ref,
								int (*f)(t_game *, t_point *,
										t_point *ok, t_point *ref));
int						farest_delta(t_game *game, t_point *pos,
								t_point *ok, t_point *ref);
int						get_nearest(t_game *game, t_point *pos,
								t_point *ok, t_point *ref);

#endif
