
#include "visitor.h"

t_ast	*visitor_visit_variable_definition(t_ast *ast)
{
}

t_ast	*visitor_visit_string(t_ast *ast)
{
}

t_ast	*visitor_visit_function_call(t_ast *ast)
{
}

t_ast	*visitor_visit_variable(t_ast *ast)
{
}

/*
 * Loop through all the compound children and visit them.
 */

t_ast	*visitor_visit_compound(t_ast *ast)
{
	int		i;

	i = 0;
	while (i < ast->compound_size)
	{
		visitor_visit(ast->compound_value[i]);
		i++;
	}
	return (init_ast(AST_NOOP));
}

/*
 * visit every node recursively and perform operations,
 * based on what kind of node type.
 * ---------------------------------------------------
 * main entry point of the VISITOR.
 * this function is going to:
 * take AST node +
 * look up what kind of type is it +
 * call appropriate child function to visit it.
 */

t_ast	*visitor_visit(t_ast *ast)
{
	switch (ast->type)
	{
		case AST_COMPOUND:
			return (visitor_visit_compound(ast));
		case AST_VARIABLE_DEFINITION:
			return (visitor_visit_variable_definition(ast));
		case AST_STRING:
			return (visitor_visit_string(ast));
		case AST_FUNCTION_CALL:
			return (visitor_visit_function_call(ast));
		case AST_VARIABLE:
			return (visitor_visit_variable(ast));
		default:
			return (init_ast(AST_NOOP));
	}
}
