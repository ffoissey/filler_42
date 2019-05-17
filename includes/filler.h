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

# define CLOSE			0x00
# define OPEN			0x01

enum				e_action
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

enum				e_state
{
	E_EMPTY,
	E_ADV,
	E_LAST_ADV,
	E_MINE,
	E_LAST_MINE,
	E_FULL,
	E_UNKNOW
};

enum				e_mode
{
	E_ANGLE_TARGET,
	E_ANGLE_OPMINE,
	E_ANGLE_OPADV,
	E_ATTACK,
	E_SPIDER_X_UP,
	E_SPIDER_X_DOWN,
	E_SPIDER_Y_LEFT,
	E_SPIDER_Y_RIGHT,
	E_CORE,
	E_EXPANSION,
	E_CONQUEST,
	E_GLUE
};



typedef unsigned char	t_way;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_mx
{
	t_point			size;
	enum e_state	**mx;
}					t_mx;

typedef	struct		s_game
{
	char			*process_name;
	t_way			**way;
	t_mx			board;
	t_mx			piece;
	enum e_action	action;
	enum e_mode		mode;
	int				row;
	char			adv_char;
	char			adv_last_char;
	char			my_char;
	char			my_last_char;
	int				get_angle;
	int				delta_adv;
	int				left_close;
	int				right_close;
	int				up_close;
	int				down_close;

	t_point			last_adv;
	t_point			nearest_adv;
	t_point			last_mine;
	t_point			core_adv;
	t_point			core_mine;

	int				nb_angle;
	int				close_angle_target;
	int				close_angle_opmine;
	int				close_angle_opadv;
	t_point			angle_target;
	t_point			angle_adv;
	t_point			angle_mine;
	t_point			angle_opmine;
	t_point			angle_opadv;
	enum e_mode		better_angle;

	t_point			contact;
	t_point			good_contact;
	int				delta_good_contact;
	t_point			to_play;
	int				turn;
}					t_game;

typedef void 			(*t_process)(t_game *, char **);
typedef unsigned char	(*t_strategy)(t_game *, t_point *);

/*
*** Action
*/

void				get_player(t_game *game, char **line);
void				get_board_first_line(t_game *game, char **line);
void				get_board(t_game *game, char **line);
void				get_size(t_game *game, char **line);
void				get_piece(t_game *game, char **line);

/*
*** Get Size
*/

int					process_size(t_point *game_size, enum e_state ***mx,
								char *line, char *type);
int					alloc_table_ways(t_game *game);

/*
*** Get Board
*/

unsigned char		check_first_line_board(unsigned int row, char *line);
int					get_line_board(t_game *game, char *line);
int					get_line_piece(t_game *game, char *line);

/*
*** Process
*/

void				ft_process(t_game *game);

/*
*** Strategy
*/

void			print_strategy(t_game *game);
void			select_strategy(t_game *game);

unsigned char	spider_y_left_mode(t_game *game, t_point *start);
unsigned char	spider_y_right_mode(t_game *game, t_point *start);
unsigned char	spider_x_up_mode(t_game *game, t_point *start);
unsigned char	spider_x_down_mode(t_game *game, t_point *start);
unsigned char	core_mode(t_game *game, t_point *start);
unsigned char	conquest_mode(t_game *game, t_point *start);
unsigned char	angle_target_mode(t_game *game, t_point *start);
unsigned char	angle_opmine_mode(t_game *game, t_point *start);
unsigned char	angle_opadv_mode(t_game *game, t_point *start);
unsigned char	attack_mode(t_game *game, t_point *start);
unsigned char	expansion_mode(t_game *game, t_point *start);
unsigned char	glue_mode(t_game *game, t_point *start);

/*
*** Utils
*/

void				speak(t_game *game, char **line);
void				error(t_game *game, char **line);
void				free_matrix(t_mx *mx);
void				free_way(t_game *game);
int					get_delta(t_point *a, t_point *b);
int					scanner(t_game *game, t_point *target,
						enum e_state state, int zone);
int					over(t_game *game, t_point *target,
						enum e_state state, int zone, float percent);
t_point				nearest(t_game *game);
int					farest_delta(t_game *game, t_point *point);
int	check_line(t_game *game, int x_or_y, int pos, enum e_state state);





void	init_way(t_game *game);

#endif
