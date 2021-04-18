
#include "lexer.h"

int		main(void)
{
	t_lexer	*lexer;
	t_token	*token;

	lexer = init_lexer("var name = \"hamid\";\n""print(name);\n");
	token = lexer_get_next_token(lexer);
	while (token->type != TOKEN_EOF)
	{
		printf("TOKEN(%s, %d)\n", token->value, token->type);
		token = lexer_get_next_token(lexer);
	}
	return (0);
}
