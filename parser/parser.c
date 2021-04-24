
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

/*
 * Expected function:
 * die if "Unexpected token", or
 * advance if "expacted token".
 */

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

/*
 * Add others Data types here.
 * integers, float, double, ...
 */

t_ast		*parser_parse_expr(t_parser *parser)
{
	switch (parser->cur_token->type)
	{
		case TOKEN_STRING:
			return (parser_parse_string(parser));
		case TOKEN_ID:
			return (parser_parse_id(parser));
		default:
			printf(
					"Unexpected token `%s', with type %d",
				   	parser->cur_token->value,
				   	parser->cur_token->type
					);
			exit(EXIT_FAILURE);
		/*
		default:
			return (init_ast(AST_NOOP));
		*/
	}
}

t_ast		*parser_parse_string(t_parser *parser)
{
	t_ast	*ast;

	ast = init_ast(AST_STRING);
	parser_expected_token(parser, TOKEN_STRING);
	ast->string_value = parser->prev_token->value;
	return (ast);
}

t_ast		*parser_parse_function_call(t_parser *parser)
{
	t_ast	*ast;
	t_ast	*ast_expr;

	ast = init_ast(AST_FUNCTION_CALL);
	ast->function_call_name = parser->prev_token->value;
	parser_expected_token(parser, TOKEN_LPAREN);
	ast->function_call_args = (t_ast **)malloc(sizeof(t_ast *));
	ast_expr = parser_parse_expr(parser);
	ast->function_call_args[0] = ast_expr;
	ast->function_call_args_size += 1;
	while (parser->cur_token->type == TOKEN_COMMA)
	{
		parser_expected_token(parser, TOKEN_COMMA);
		ast->function_call_args_size += 1;
		ast->function_call_args = realloc(
				ast->function_call_args,
				ast->function_call_args_size * sizeof(t_ast *)
				);
		ast_expr = parser_parse_expr(parser);
		ast->function_call_args[ast->function_call_args_size - 1] = ast_expr;
	}
	parser_expected_token(parser, TOKEN_RPAREN);
	return (ast);
}

t_ast		*parser_parse_variable(t_parser *parser)
{
	t_ast	*ast;
	char	*variable_value;

	parser_expected_token(parser, TOKEN_ID);
	if (parser->cur_token->type == TOKEN_LPAREN)
		return (parser_parse_function_call(parser));
	variable_value = parser->prev_token->value;
	ast = init_ast(AST_VARIABLE);
	ast->variable_value = variable_value;
	return (ast);
}

t_ast		*parser_parse_variable_definition(t_parser *parser)
{
	t_ast	*ast;
	t_ast	*var_def_value;
	char	*var_def_name;

	parser_expected_token(parser, TOKEN_ID);
	parser_expected_token(parser, TOKEN_ID);
	var_def_name = parser->prev_token->value;
	parser_expected_token(parser, TOKEN_EQUALS);
	var_def_value = parser_parse_expr(parser);
	ast = init_ast(AST_VARIABLE_DEFINITION);
	ast->var_def_name = var_def_name;
	ast->var_def_value = var_def_value;
	return (ast);
}

t_ast		*parser_parse_id(t_parser *parser)
{
	if (strcmp(parser->cur_token->value, "var") == 0)
		return (parser_parse_variable_definition(parser));
	else
		return (parser_parse_variable(parser));
}

t_ast		*parser_parse_statement(t_parser *parser)
{
	switch (parser->cur_token->type)
	{
		case TOKEN_ID:
			return (parser_parse_id(parser));
		default:
			printf(
					"Unexpected token `%s', with type %d",
				   	parser->cur_token->value,
				   	parser->cur_token->type
					);
			exit(EXIT_FAILURE);
		/*
		default:
			return (init_ast(AST_NOOP));
		*/
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
	while (1)
	{
		parser_expected_token(parser, TOKEN_SEMI);
		if (parser->cur_token->type == TOKEN_EOF)
			break ;
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

/*
 * main entry point of the PARSER.
 * return whole AST tree of our entire source code.
 * this function return the source code but as an AST tree.
 */

t_ast		*parser_parse(t_parser *parser)
{
	return (parser_parse_statements(parser));
}
