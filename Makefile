
NAME = hello.out

SRCS = main.c \
	   ./lexer/token.c \
	   ./lexer/lexer.c \
	   ./parser/parser.c \
	   ./ast/ast.c \
	   ./executor/visitor.c

INCLUDES = ./lexer/token.h \
		   ./lexer/lexer.h \
		   ./parser/parser.h \
		   ./ast/ast.h \
		   ./executor/visitor.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCS) $(INCLUDES)
	@gcc $(FLAGS) $(SRCS) -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean:
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
