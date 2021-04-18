
#include "parser.h"

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	parser->lexer = lexer;
	parser->cur_token = lexer_get_next_token(lexer);
	parser->prev_token = parser->cur_token;
	return (parser);
}

void		parser_expected_token(t_parser *parser, t_token_type type)
{
	if (parser->cur_token->type == type)
	{
		parser->prev_token = parser->cur_token;
		parser->cur_token = lexer_get_next_token(parser->lexer);
	}
	else
	{
		printf(
				"Unexpected token `%s', with type %d",
				parser->cur_token->value, parser->cur_token->type
				);
		exit(EXIT_FAILURE);
	}
}

t_ast		*parser_parse_statement(t_parser *parser)
{
	switch (parser->cur_token->type)
	{
		case TOKEN_ID:
			return (parser_parse_id(parser));
	}
}

t_ast		*parser_parse_statements(t_parser *parser)
{
	t_ast	*ast;
	t_ast	*ast_statement;

	ast = init_ast(AST_COMPOUND);
	ast->compound_value = (t_ast **)malloc(sizeof(t_ast *));
	ast_statement = parser_parse_statement(parser);
	ast->compound_value[0] = ast_statement;
	ast->compound_size += 1;
	while (parser->cur_token->type == TOKEN_SEMI)
	{
		parser_expected_token(parser, TOKEN_SEMI);
		ast->compound_size += 1;
		ast->compound_value = realloc(
				ast->compound_value,
				ast->compound_size * sizeof(t_ast *)
				);
		ast_statement = parser_parse_statement(parser);
		ast->compound_value[ast->compound_size - 1] = ast_statement;
	}
	return (ast);
}

t_ast		*parser_parse_string(t_parser *parser)
{
}

t_ast		*parser_parse_variable(t_parser *parser)
{
}

t_ast		*parser_parse_variable_definition(t_parser *parser)
{
}

t_ast		*parser_parse_function_call(t_parser *parser)
{
}

t_ast		*parser_parse_id(t_parser *parser)
{
}

t_ast		*parser_parse_expr(t_parser *parser)
{
}

/*
 * main entry point of the PARSER.
 * return whole AST tree of our entire source code.
 * this function return the source code but as an AST tree.
 */

t_ast		*parser_parse(t_parser *parser)
{
	return (parser_parse_statements(parser));
}
