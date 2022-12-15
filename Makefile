NAME		= minishell

SRCS		= src/main.c

OBJS		= $(SRCS:%.c=%.o)

LIBFT_DIR	= libft
LIBFT = libft.a

CCF			= gcc -Wall -Wextra -Werror

RL_INC		=	-I /usr/local/opt/readline/include
RL_LINK		=	-L /usr/local/opt/readline/lib -l readline
INC_DIR		=	include
SRC_DIR		=	src
OBJ_DIR		=	objects

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

all: $(NAME)

$(LIBFT):	
			@make -C $(LIBFT_DIR) all

$(NAME): $(LIBFT) $(OBJS)
			$(CCF) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(RL_LINK) -o $(NAME)
			echo "$(TURQUOISE)\n\tComplited $(NAME)!\n$(END)"

#-L /usr/local/opt/readline/lib

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
			@mkdir -p $(OBJ_DIR)
			@printf $(YELLOW)
			$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR) $(RL_INC) -c $< -o $@

#-I include/

clean:
			$(RM) $(OBJS)
			$(MAKE) -C libft/ clean
			echo "$(BLUE)\n\tCleaning succeed!!\n$(END)"

fclean: clean
			$(RM) $(NAME)
			$(MAKE) -C libft/ fclean
			echo "$(GRY)\n\tAll files were deleted!\n$(END)"

re: fclean all