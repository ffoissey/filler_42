#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
# include "sys/ioctl.h"

# define PLAYER_ONE 	"$$$ exec p1 : ["
# define PLAYER_TWO 	"$$$ exec p2 : ["
# define GOT_P1 		"<got (O): ["
# define GOT_P2			"<got (X): ["
# define PLAYER_SIZE 	15
# define GOT_SIZE	 	11
# define EMPTY			'.'
# define FULL			'*'
# define P1_CHAR		'O'
# define P1_LAST_CHAR	'o'
# define P2_CHAR		'X'
# define P2_LAST_CHAR	'x'
# define PLATEAU		"Plateau"
# define PIECE			"Piece"
# define ERROR			"ERROR"
# define WINNER			"WINNER\n"
# define INFO			"FILLER STAT"
# define LEN_P			44

# define BLUE			"\033[44m  "
# define BLUE_ONE		"\033[44m "
# define CYAN			"\033[46m  "
# define RED			"\033[41m  "
# define RED_ONE		"\033[41m "
# define PURPLE			"\033[45m "
# define YELLOW			"\033[43m  "
# define WHITE			"\033[47m  "
# define GREEN			"\033[42m  "
# define NC				"\033[0m"
# define DELAY			50000000


enum				e_state
{
	E_EMPTY,
	E_P1,
	E_LAST_P1,
	E_P2,
	E_LAST_P2,
	E_FULL,
	E_UNKNOW
};

enum				e_action
{
	E_GET_PLAYER,
	E_GET_BOARD_SIZE,
	E_GET_BOARD_FIRST_LINE,
	E_GET_BOARD,
	E_GET_PIECE_SIZE,
	E_GET_PIECE,
	E_GET_POS,
	E_PRINT,
	E_ERROR,
	E_SLEEP
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
	char			*p1_name;
	char			*p2_name;
	enum e_action	action;
	t_mx			board;
	t_mx			piece;
	int				row;
	t_point			core_p1;
	t_point			core_p2;
	t_point			last_pos;
	int				score_p1;
	int				score_p2;
	int				last_score_p1;
	int				last_score_p2;
}					t_game;


typedef void 			(*t_process)(t_game *, char **);

/*
*** Action
*/

void				get_player(t_game *game, char **line);
void				get_board_first_line(t_game *game, char **line);
void				get_board(t_game *game, char **line);
void				get_size(t_game *game, char **line);
void				get_piece(t_game *game, char **line);
void				get_pos(t_game *game, char **line);

/*
*** Get Size
*/

int					process_size(t_point *game_size, enum e_state ***mx,
								char *line, char *type);

/*
*** Get Board
*/

unsigned char		check_first_line_board(unsigned int row, char *line);
int					get_line_board(t_game *game, char *line);
int					get_line_piece(t_game *game, char *line);


/*
*** Utils
*/

void				free_matrix(t_mx *mx);
void				print_board(t_game *game, int end);

#endif
