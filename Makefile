# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/10 10:00:43 by cmariot           #+#    #+#              #
#    Updated: 2021/09/26 14:08:16 by cmariot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#### PIPEX ###

PROGRAM = pipex

PROGRAM_DIR = srcs

PROGRAM_OBJS = ${PROGRAM_SRCS:.c=.o}

PROGRAM_SRCS = ${PROGRAM_DIR}/main.c \
			   ${PROGRAM_DIR}/execute_cmd.c


### COMPILATION ###

COMPILER = gcc

COMPILER_FLAGS = -Wall -Wextra -Werror

INCLUDES_DIR = includes

REMOVE = rm -rf

.c.o:
				@${COMPILER} ${COMPILER_FLAGS} -g -c $< -o ${<:.c=.o} -I ${INCLUDES_DIR} -I ${LIBFT_DIR}

${PROGRAM}:		program_compil

program_compil: compil_libft ${PROGRAM_OBJS}
				@${COMPILER} ${COMPILER_FLAGS} ${PROGRAM_OBJS} -I ${INCLUDES_DIR} -L ${LIBFT_DIR} -lft -o ${PROGRAM}
				@printf "The pipex program is ready.\n"

all:			program_compil


#### TEST ####

test:			program_compil
				@cp Makefile file1
				./pipex file1 "grep src" "wc -l" file2

#### LIBFT ####

LIBFT_DIR = libft

compil_libft:
				@cd ${LIBFT_DIR} && make


#### NORM ####

norm:
				norminette
				@printf "The norm is checked.\n"


#### CLEAN ####

clean:
				@cd libft && make clean
				@${REMOVE} ${PROGRAM_OBJS}
				@printf "The object files have been deleted.\n"

fclean:			
				@cd libft && make fclean
				@${REMOVE} ${PROGRAM_OBJS}
				@${REMOVE} ${PROGRAM}
				@${REMOVE} file1 file2
				@printf "The object and binary files have been deleted.\n"

re:				fclean all

.PHONY:			clean fclean
