NAME		=	minishell

LIBFT_DIR	=	libft
LIBFT		=	libft.a
RL_INC		=	-I /usr/local/opt/readline/include
RL_LINK		=	-L /usr/local/opt/readline/lib -l readline

INC_DIR		=	include
SRC_DIR		=	src
OBJ_DIR		=	objects

SRCS		=	src/main.c			\
				builtin/echo.c		\
				parsing/parse.c		\
				parsing/utils1.c	\
				parsing/utils2.c	\
				parsing/utils3.c	\

OBJS		=	$(SRCS:%c=%o)

CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -Werror -fsanitize=address
RM			=	rm -rf

all:		$(NAME)

%.o : %.c
# @mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) $(RL_INC) -c $< -o $@

$(NAME):	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(RL_LINK) -o $@

$(LIBFT):
			@make -C $(LIBFT_DIR) all

clean:
			@make -C $(LIBFT_DIR) fclean
			$(RM) ./src/*.o
			$(RM) ./parsing/*.o
			$(RM) ./builtin/*.o
# @make -C $(GNL_DIR) fclean
			@$(RM) $(OBJ_DIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

# NAME		= minishell

# SRCS		=	src/main.c		\
# 				builtin/echo.c	\
# 				parsing/parse.c	\
# 				parsing/utils1.c	\

# OBJS		= $(SRCS:%c=%o)

# LIBFT_DIR	= libft
# LIBFT = libft.a

# CC			= gcc
# CFLAGS		= -Wall -Wextra -Werror

# RL_INC		=	-I /usr/local/opt/readline/include
# RL_LINK		=	-L /usr/local/opt/readline/lib -l readline
# # RL_INC		=	-I .brew/opt/readline/include
# # RL_LINK		=	-L .brew/opt/readline/lib
# INC_DIR		=	include
# SRC_DIR		=	src
# OBJ_DIR		=	objects

# RM			= rm -rf

# #---------------------------------------------------------------------------------
# GRY			=	\033[1;30m
# RED			=	\033[1;31m
# WHITE		=	\033[1;32m
# BLUE		=	\033[1;34m
# YELLOW		=	\033[1;33m
# PUPURE		=	\033[1;35m
# TURQUOISE	=	\033[36;1m
# END			=	\033[0m
# #---------------------------------------------------------------------------------

# $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
# 			mkdir -p $(OBJ_DIR)
# 			@printf $(YELLOW)
# 			@printf hi
# 			$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) $(RL_INC) -c $< -o $@

# all: $(NAME)
# 		@echo "PICOSHELL"
# 		@echo "_______________	_____________  _______________  __________________"
# 		@echo "|			 |  	  |		   |			   |				  |"
# 		@echo "|			 |  	  |		   |			   |				  |"
# 		@echo "|			 |  	  |		   |			   |				  |"
# 		@echo "|			 |  	  |		   |			   |				  |"
# 		@echo "|			 |  	  |		   |			   |				  |"
# 		@echo "|_____________|  	  |		   |			   |				  |"
# 		@echo "|					  |		   |			   |				  |"
# 		@echo "|					  |		   |			   |				  |"
# 		@echo "|					  |		   |			   |				  |"
# 		@echo "|					  |		   |			   |				  |"
# 		@echo "|					  |		   |			   |				  |"
# 		@echo "|					  |		   |			   |				  |"
# 		@echo "|					  |		   |			   |				  |"
# 		@echo "|				 _____|_____   |_____________  |__________________|"

# $(NAME): $(LIBFT) $(OBJS)
# 			@printf hello
# 			$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(RL_LINK) -o $(NAME)
# 			echo "$(TURQUOISE)\n\tComplited $(NAME)!\n$(END)"

# $(LIBFT):	
# 			@make -C $(LIBFT_DIR) all
# #-L /usr/local/opt/readline/lib


# #-I include/

# clean:
# 			$(RM) $(OBJS)
# 			$(MAKE) -C libft/ clean
# 			echo "$(BLUE)\n\tCleaning succeed!!\n$(END)"

# fclean: clean
# 			$(RM) $(NAME)
# 			$(MAKE) -C libft/ fclean
# 			echo "$(GRY)\n\tAll files were deleted!\n$(END)"

# re: fclean all

# .PHONY: all clean fclean re libft