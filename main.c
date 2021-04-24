
#include "./executor/visitor.h"

int		main(void)
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast		*ast;
	t_visitor	*visitor;

	lexer = init_lexer("var name = \"naji\";\n""print(name);\n");
	parser = init_parser(lexer);
	ast = parser_parse(parser);
	visitor = init_visitor();
	visitor_visit(ast, visitor);
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
