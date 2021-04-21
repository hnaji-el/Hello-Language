
#include "parser.h"

int		main(void)
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast		*ast;

	lexer = init_lexer("var name = \"hamid\";\n""print(name, name1);\n");
	parser = init_parser(lexer);
	ast = parser_parse(parser);
	printf(
			"%d\n%d\n%s\n",
			ast->type,
			ast->compound_size,
			);
	return (0);

	/*
	t_token		*token;
	t_lexer		*lexer;

	lexer = init_lexer("{var name = \"hamid\";\n""print(name);\n");
	token = lexer_get_next_token(lexer);
	while (token->type != TOKEN_EOF)
	{
		printf("TOKEN(%s, %d)\n", token->value, token->type);
		token = lexer_get_next_token(lexer);
	}
	*/
	return (0);
}
