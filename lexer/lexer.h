
#ifndef LEXER_H
# define LEXER_H

#include "token.h"

typedef struct	s_lexer
{
	char	*source;
	int		cur_index;
	char	cur_char;
	int		len_of_src;
}				t_lexer;

t_lexer	*init_lexer(char *source);

void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespaces(t_lexer *lexer);

t_token	*lexer_get_next_token(t_lexer *lexer);

char	*lexer_get_current_char_as_string(t_lexer *lexer);
t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token);

t_token	*lexer_collect_id(t_lexer *lexer);
t_token	*lexer_collect_string(t_lexer *lexer);

#endif
