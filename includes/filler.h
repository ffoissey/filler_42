#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

# define PLAYER_ONE 	"$$$ exec p1 : ["
# define PLAYER_TWO 	"$$$ exec p2 : ["
# define PLAYER_SIZE 	15
# define NAME 			"/ffoissey.filler]\0"
# define DEBUG_NAME 	"/debug_ffoissey.filler]\0"
# define EMPTY			'.'
# define FULL			'*'
# define P1_CHAR		'O'
# define P1_LAST_CHAR	'o'
# define P2_CHAR		'X'
# define P2_LAST_CHAR	'x'
# define PLATEAU		"Plateau"
# define PIECE			"Piece"

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
	E_ANGLE,
	E_ATTACK,
	E_SPIDER_X,
	E_SPIDER_Y,
	E_CORE,
	E_EXPANSION
};

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
	t_mx			board;
	t_mx			piece;
	char			adv_char;
	char			adv_last_char;
	char			my_char;
	char			my_last_char;
	int				row;
	enum e_action	action;
	enum e_mode		mode;

	t_point			last_adv;
	t_point			last_mine;
	t_point			core_adv;
	t_point			core_mine;
	t_point			angle;

	t_point			to_play;
	t_point			contact; // USE ?
}					t_game;

typedef void 			(*t_process)(t_game *, char **);
typedef unsigned char	(*t_strategy)(t_game *, t_point *);

/*
*** Action
*/

void				error(t_game *game, char **line);
void				get_player(t_game *game, char **line);
void				get_board_size(t_game *game, char **line);
void				get_board_first_line(t_game *game, char **line);
void				get_board(t_game *game, char **line);
void				get_piece_size(t_game *game, char **line);
void				get_piece(t_game *game, char **line);
void				speak(t_game *game, char **line);

/*
*** Get Size
*/

int					get_size(t_point *game_size, enum e_state ***mx,
								char *line, char *type);

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

unsigned char	spider_y_mode(t_game *game, t_point *start);
unsigned char	spider_x_mode(t_game *game, t_point *start);
unsigned char	core_mode(t_game *game, t_point *start);
unsigned char	angle_mode(t_game *game, t_point *start);
unsigned char	attack_mode(t_game *game, t_point *start);
unsigned char	expansion_mode(t_game *game, t_point *start);

/*
*** Utils
*/

void				free_matrix(t_mx *mx);
int					get_delta(t_point *a, t_point *b);
int					scanner(t_game *game, t_point *target,
						enum e_state state, int zone);

#endif
