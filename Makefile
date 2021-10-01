# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/30 11:15:47 by cmariot           #+#    #+#              #
#    Updated: 2021/09/30 18:20:21 by cmariot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
#                          PROJECT'S DIRECTORIES                               #
# **************************************************************************** #

NAME		= pipex
SRCS_DIR	= srcs
INCL_DIR	= includes
LIBFT_DIR	= libft
OBJS_DIR	= objs/


# **************************************************************************** #
#                         COMPILATION AND LINK FLAGS                           #
# **************************************************************************** #

CC					= gcc

CFLAGS				= -Wall -Wextra -Werror
CFLAGS				+= -I $(INCL_DIR)
CFLAGS				+= -I $(LIBFT_DIR)

LFLAGS				= -Wall -Wextra -Werror
LFLAGS				+= -L $(LIBFT_DIR) -lft

# Debug flag, use with 'make DEBUG=1'
ifeq ($(DEBUG), 1)
	CFLAGS			+= -g
endif


# **************************************************************************** #
#                                SOURCE FILES                                  #
# **************************************************************************** #

SRCS		= main.c \
			  single_redirection.c \
			  double_redirection.c \
			  execute_cmd.c \
			  multiple_pipelines_bonus.c

SRC			:= $(notdir $(SRCS))

OBJ			:= $(SRC:.c=.o)

OBJS		:= $(addprefix $(OBJS_DIR), $(OBJ))

VPATH		:= $(SRCS_DIR) $(OBJS_DIR) $(shell find $(SRCS_DIR) -type d)


# **************************************************************************** #
#									COLORS                                     #
# **************************************************************************** #

GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m


# **************************************************************************** #
#                             MAKEFILE'S RULES                                 #
# **************************************************************************** #

all : $(NAME)

header :
		@printf "        _\n  _ __ (_)_ __   _____  __\n | '_ \| | '_ \ / _ \ \/ /\n | |_) | | |_) |  __/>  <\n | .__/|_| .__/ \___/_/\_\ \n |_|     |_|\n\n"

# Compiling
$(OBJS_DIR)%.o : %.c
		@mkdir -p $(OBJS_DIR)
		@$(CC) $(CFLAGS) -c $< -o $@
		@printf "$(YE)$(CC) $(CFLAGS) -c $< -o $@ ✅ \n$(RC)"

libft_compil:
		@printf "$(YE)Libft compilation ... "
		@make -C libft
		@printf "Success !$(RC)\n\n"

srcs_compil :
		@printf "$(YE)Source code compilation ... \n$(RC)"
			
# Linking
$(NAME)	: header libft_compil srcs_compil $(SRCS) $(OBJS)
		@printf "$(YE)$(NAME) compilation success !\n\n$(RC)"
		@printf "$(GR)Object files linking ...\n$(CC) $(LFLAGS) $(OBJS) $(RC)\n"
		@$(CC) $(LFLAGS) $(OBJS) -o $(NAME)
		@printf "$(GR)Success !\n$(NAME) is ready.\n\n$(RC)"
		@printf "Mandatory usage : ./pipex file1 'cmd1' 'cmd2' file2\n"
		@printf "Bonus usage : ./pipex here_doc limiter 'cmd1' 'cmd2' file2\n\n"

# Check 42 norm 
norm :
		@norminette

test:	${NAME}
		@cp Makefile file1
		./pipex file1 "grep .c" "wc -l" file2

bonus_test:	${NAME}
		./pipex here_doc stop "grep e" "wc -l" file2

# Remove object files
clean :
		@printf "$(RE)Removing $(OBJS_DIR) ... $(RC)"
		@rm -rf $(OBJS_DIR)
		@printf "$(RE)Done$(RC)\n"
		@printf "$(RE)Cleaning libft ... $(RC)"
		@make clean -C libft
		@printf "$(RE)Done$(RC)\n"

# Remove object and binary files
fclean : clean
		@printf "$(RE)Removing $(NAME) ... $(RC)"
		@rm -f $(NAME)
		@printf "$(RE)Done$(RC)\n"
		@printf "$(RE)Removing libft.a ... $(RC)"
		@make fclean -C libft
		@printf "$(RE)Done$(RC)\n"

# Remove all and recompile
re :	 fclean all

.PHONY : clean fclean
