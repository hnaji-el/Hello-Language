
#ifndef AST_H
# define AST_H

#include <stdlib.h>

typedef enum	e_ast_type
{
	AST_COMPOUND,
	AST_VARIABLE_DEFINITION,
	AST_STRING,
	AST_FUNCTION_CALL,
	AST_VARIABLE,
	AST_NOOP
}				t_ast_type;

typedef struct	s_ast
{
	t_ast_type		type;
	/* AST_COMPOUND */
	struct s_ast	**compound_value;
	int				compound_size;
	/* AST_VARIABLE_DEFINITION */
	char			*var_def_name;
	struct s_ast	*var_def_value;
	/* AST_STRING */
	char			*string_value;
	/* AST_FUNCTION_CALL */
	char			*function_call_name;
	struct s_ast	**function_call_args;
	int				function_call_args_size;
	/* AST_VARIABLE */
	char			*variable_value;
}				t_ast;

t_ast	*init_ast(t_ast_type type);

#endif
