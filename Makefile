NAME		= minishell

SRCS		= src/main.c

OBJS		= $(SRCS:%.c=%.o)

LIB			= libft/libft.a

CCF			= gcc -Wall -Wextra -Werror

HEADER		= include/minishell.h

READLINE	= -l readline

RM			= rm -rf

#---------------------------------------------------------------------------------
GRY			=	\033[1;30m
RED			=	\033[1;31m
WHITE		=	\033[1;32m
BLUE		=	\033[1;34m
YELLOW		=	\033[1;33m
PUPURE		=	\033[1;35m
TURQUOISE	=	\033[36;1m
END			=	\033[0m
#---------------------------------------------------------------------------------

.PHONY: all clean fclean re libft

all: libft $(NAME)

libft:
			$(MAKE) -C libft/

$(NAME): $(OBJS)
			$(CCF) $(READLINE) $(OBJS) $(LIB) -o $(NAME)
			echo "$(TURQUOISE)\n\tComplited $(NAME)!\n$(END)"

%.o: %.c $(HEADER)
			$(CCF) -c $< -o $@ -I $(HEADER)

clean:
			$(RM) $(OBJS)
			$(MAKE) -C libft/clean
			echo "$(BLUE)\n\tCleaning succeed!!\n$(END)"

fclean: clean
			$(RM) $(NAME)
			$(MAKE) -C libft/fclean
			echo "$(GRY)\n\tAll files were deleted!\n$(END)"

re: fclean all
			echo "$(YELLOW)\n\tRemake done!\n$(END)"
