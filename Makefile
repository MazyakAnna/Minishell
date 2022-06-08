# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fserwyn <fserwyn@student.21-school.r>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/03 18:05:11 by fserwyn           #+#    #+#              #
#    Updated: 2021/11/20 08:25:01 by bmaegan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = -L./libft/ -lft

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = main.c \
	builtins.c \
	builtin_cd.c \
	builtin_env.c \
	builtin_exit.c \
	builtin_export.c \
	cleaner.c \
	command_utils.c \
	common_utils.c \
	common_utils2.c \
	common_utils3.c \
	double_str_utils.c \
	expand_env.c \
	expansions.c \
	expansions2.c \
	ft_pipex.c \
	get_cmd.c \
	get_env_path.c \
	get_next_line.c \
	get_next_line_utils.c \
	here_doc.c \
	inits.c \
	parse_commands.c \
	parse_operators.c \
	pipe_parts.c \
	print_structs.c \
	run_simple_command.c \
	signal.c \
	sort_double_arr.c \
	token_recognition.c \
	token_utils.c \
	utils.c

HEADER = mini.h \
		structs.h \
		defines.h \

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

HEADERS = $(HEADER:%=$(INC_DIR)/%)
SRCS = $(SRC:%=$(SRC_DIR)/%)

INCS = -I$(HOME)/.brew/opt/readline/include -I./libft -I$(INC_DIR)
READLINELIB = -L$(HOME)/.brew/opt/readline/lib -lreadline
MAKE = make

OBJ = $(SRC:.c=.o)
OBJS = $(OBJ:%=$(OBJ_DIR)/%)

all:	$(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile $(HEADERS)
	$(CC) $(CFLAGS) $(INCS)  -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJS)
	$(MAKE) -C ./libft/
	$(CC) $(CFLAGS) $(READLINELIB) $(LIBFT) $(OBJS) -o $(NAME)

bonus: all

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJ) $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)


re: fclean all

#.PHONY: all clean fclean re bonus
