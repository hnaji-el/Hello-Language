
#include "visitor.h"

t_visitor	*init_visitor(void)
{
	t_visitor	*visitor;

	visitor = (t_visitor *)malloc(sizeof(t_visitor));
	visitor->variable_definitions = (void *)0;
	visitor->variable_definitions_size = 0;
	return (visitor);
}

t_ast	*visitor_visit_string(t_ast *node, t_visitor *visitor)
{
	t_visitor	*vis;

	vis = visitor;
	return (node);
}

t_ast	*visitor_visit_variable(t_ast *node, t_visitor *visitor)
{
	t_ast	*vardef;
	int		i;

	i = 0;
	while (i < visitor->variable_definitions_size)
	{
		vardef = visitor->variable_definitions[i];
		if (strcmp(node->variable_value, vardef->var_def_name) == 0)
			return (visitor_visit(vardef->var_def_value, visitor));
		i++;
	}
	printf(
			"Undefined variable `%s'\n",
			node->variable_value
			);
	exit(EXIT_FAILURE);
}

t_ast	*builtin_function_print(t_ast *node, t_visitor *visitor)
{
	t_ast	*var_value;
	int		i;

	i = 0;
	while (i < node->function_call_args_size)
	{
		var_value = visitor_visit(node->function_call_args[i], visitor);
		switch (var_value->type)
		{
			case AST_STRING:
				printf("%s\n", var_value->string_value);
				break ;
			default:
				printf("Undefined data type with type `%d' \n", var_value->type);
				exit(EXIT_FAILURE);
		}
		i++;
	}
	return (init_ast(AST_NOOP));
}

t_ast	*visitor_visit_function_call(t_ast *node, t_visitor *visitor)
{
	int		i;

	i = 0;
	if (strcmp(node->function_call_name, "print") == 0)
		return (builtin_function_print(node, visitor));
	printf(
			"Undefined function `%s'\n",
			node->function_call_name
			);
	exit(EXIT_FAILURE);
}

t_ast	*visitor_visit_variable_definition(t_ast *node, t_visitor *visitor)
{
	if (visitor->variable_definitions == (void *)0)
	{
		visitor->variable_definitions = (t_ast **)malloc(sizeof(t_ast *));
		visitor->variable_definitions[0] = node;
		visitor->variable_definitions_size += 1;
	}
	else
	{
		visitor->variable_definitions_size += 1;
		visitor->variable_definitions = realloc(
				visitor->variable_definitions,
				visitor->variable_definitions_size * sizeof(t_ast *)
				);
		visitor->variable_definitions[visitor->variable_definitions_size - 1] = node;
	}
	return (node);
}

/*
 * Loop through all the compound children and visit them.
 */

t_ast	*visitor_visit_compound(t_ast *node, t_visitor *visitor)
{
	int		i;

	i = 0;
	while (i < node->compound_size)
	{
		visitor_visit(node->compound_value[i], visitor);
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

t_ast	*visitor_visit(t_ast *node, t_visitor *visitor)
{
	switch (node->type)
	{
		case AST_COMPOUND:
			return (visitor_visit_compound(node, visitor));
		case AST_VARIABLE_DEFINITION:
			return (visitor_visit_variable_definition(node, visitor));
		case AST_STRING:
			return (visitor_visit_string(node, visitor));
		case AST_FUNCTION_CALL:
			return (visitor_visit_function_call(node, visitor));
		case AST_VARIABLE:
			return (visitor_visit_variable(node, visitor));
		case AST_NOOP:
			return (node);
	}
	printf("Uncaught statement of type `%d'\n", node->type);
	exit(EXIT_FAILURE);
}
