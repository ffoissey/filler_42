#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

# define PLAYER_ONE 	"$$$ exec p1 : [ffoissey.filler]"
# define PLAYER_TWO 	"$$$ exec p2 : [ffoissey.filler]"
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


typedef struct		s_point
{
	unsigned int	x;
	unsigned int	y;
}					t_point;

typedef	struct		s_game
{
	enum e_state	**board;
	enum e_state	**piece;
	unsigned int	row;
	t_point			board_size;
	t_point			piece_size;
	t_point			adv_nearest;
	t_point			to_play;
	char			adv_char;
	char			adv_last_char;
	char			my_char;
	char			my_last_char;
	enum e_action	action;
}					t_game;

typedef void (*t_process)(t_game *, char **);

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

void	ft_process(t_game *game);

#endif
