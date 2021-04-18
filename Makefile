
NAME = hello.out

SRCS = main.c token.c lexer.c parser.c ast.c

INCLUDES = token.h lexer.h parser.h ast.h

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
