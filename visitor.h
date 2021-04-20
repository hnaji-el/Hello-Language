
#ifndef VISITOR_H
# define VISITOR_H

# include "parser.h"

typedef struct	s_visitor
{
	t_ast	**variable_definition;
	int		variable_definition_size;
}				t_visitor;

t_ast	*visitor_visit(t_ast *ast);

t_ast	*visitor_visit_compound(t_ast *ast);

t_ast	*visitor_visit_variable_definition(t_ast *ast);

t_ast	*visitor_visit_string(t_ast *ast);

t_ast	*visitor_visit_function_call(t_ast *ast);

t_ast	*visitor_visit_variable(t_ast *ast);

#endif
