
NAME = hello.out

SRCS = main.c token.c lexer.c

INCLUDES = token.h lexer.h

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
