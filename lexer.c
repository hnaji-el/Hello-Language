
#include "lexer.h"

t_lexer	*init_lexer(char *source)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	lexer->source = source;
	lexer->cur_index = 0;
	lexer->cur_char = source[0];
	lexer->len_of_src = strlen(source);
	return (lexer);
}

/*
 * Helper functions of the LEXER
 */

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->cur_char != '\0' && lexer->cur_index < lexer->len_of_src)
	{
		lexer->cur_index += 1;
		lexer->cur_char = lexer->source[lexer->cur_index];
	}
}

void	lexer_skip_whitespaces(t_lexer *lexer)
{
	while (lexer->cur_char == ' ' || lexer->cur_char == '\n')
		lexer_advance(lexer);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = lexer->cur_char;
	str[1] = '\0';
	return (str);
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*value;
	char	*str;

	value = (char *)malloc(sizeof(char));
	value[0] = '\0';
	while (isalnum(lexer->cur_char))
	{
		str = lexer_get_current_char_as_string(lexer);
		value = realloc(value, strlen(str) + strlen(value) + 1);
		strcat(value, str);
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_ID, value));
}

t_token	*lexer_collect_string(t_lexer *lexer)
{
	char	*value;
	char	*str;

	value = (char *)malloc(sizeof(char));
	value[0] = '\0';
	lexer_advance(lexer);
	while (lexer->cur_char != '"')
	{
		str = lexer_get_current_char_as_string(lexer);
		value = realloc(value, strlen(str) + strlen(value) + 1);
		strcat(value, str);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (init_token(TOKEN_STRING, value));
}

/*
 * main entry point of the LEXER.
 * Heart and Soul of the lexer.
 */

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->cur_char != '\0' && lexer->cur_index < lexer->len_of_src)
	{
		if (lexer->cur_char == ' ' || lexer->cur_char == '\n')
			lexer_skip_whitespaces(lexer);
		if (lexer->cur_char == '"')
			return (lexer_collect_string(lexer));
		if (isalnum(lexer->cur_char))
			return (lexer_collect_id(lexer));
		switch (lexer->cur_char)
		{
			case '=':
				return (lexer_advance_with_token(lexer, init_token(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer))));
			case '(':
				return (lexer_advance_with_token(lexer, init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer))));
			case ')':
				return (lexer_advance_with_token(lexer, init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer))));
			case ';':
				return (lexer_advance_with_token(lexer, init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer))));
			case ',':
				return (lexer_advance_with_token(lexer, init_token(TOKEN_COMMA, lexer_get_current_char_as_string(lexer))));
			default:
				return (lexer_advance_with_token(lexer, init_token(TOKEN_NO_TOKEN, lexer_get_current_char_as_string(lexer))));
		}
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_EOF, "\0"));
}
