
#include "ast.h"

t_ast	*init_ast(t_ast_type type)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	ast->type = type;
	/* AST_COMPOUND */
	ast->compound_value = (void *)0;
	ast->compound_size = 0;
	/* AST_VARIABLE_DEFINITION */
	ast->var_def_name = (void *)0;
	ast->var_def_value = (void *)0;
	/* AST_STRING */
	ast->string_value = (void *)0;
	/* AST_FUNCTION_CALL */
	ast->function_call_name = (void *)0;
	ast->function_call_args = (void *)0;
	ast->function_call_args_size = 0;
	/* AST_VARIABLE */
	ast->variable_value = (void *)0;
	return (ast);
}
