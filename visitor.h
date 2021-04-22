
#ifndef VISITOR_H
# define VISITOR_H

# include "parser.h"

typedef struct	s_visitor
{
	t_ast	**variable_definitions;
	int		variable_definitions_size;
}				t_visitor;

t_visitor	*init_visitor();

t_ast		*visitor_visit(t_ast *node, t_visitor *visitor);

t_ast		*visitor_visit_compound(t_ast *node, t_visitor *visitor);
t_ast		*visitor_visit_variable_definition(t_ast *node, t_visitor *visitor);
t_ast		*visitor_visit_string(t_ast *node, t_visitor *visitor);
t_ast		*visitor_visit_function_call(t_ast *node, t_visitor *visitor);
t_ast		*visitor_visit_variable(t_ast *node, t_visitor *visitor);

#endif
