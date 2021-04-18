
#ifndef TOKEN_H
# define TOKEN_H

# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>

typedef enum	e_token_type
{
	TOKEN_ID,
	TOKEN_EQUALS,
	TOKEN_STRING,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_SEMI,
	TOKEN_EOF
}				t_token_type;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
}				t_token;

t_token	*init_token(t_token_type type, char *value);

#endif
