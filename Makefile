# this is to manage flags for m1 architecture, we don't have to use this flag in linux
OS_ARCH 	:= $(shell uname -m)
ifeq ($(OS_ARCH),arm64)
	RL_INC 	:= -I /opt/homebrew/opt/readline/include
	RL_LIB	:= -L /opt/homebrew/opt/readline/lib
	OS_NAME := Mac M1
else
	OS_NAME := Linux
endif

HEADER_INC	:=	-I./include

LIBFT_PATH	:=	./libft/

SRC_PATH	=	./src/

SRCS		=	main.c \
				painter.c \
				utils.c \
				signal.c \
				$(addprefix parsing/, parse.c error_op.c error_quote.c init_cmd.c manage_cmd.c getter_cmd.c)\
				$(addprefix exec/, env_utils.c here_doc.c open.c redir_utils.c exec_ve.c error.c reset_redir.c\
				exec.c pipe.c free.c redir.c lib/ft_quote_split.c lib/ft_free_split.c)\
				$(addprefix exec/builtin/, cd.c unset.c export.c echo.c env.c pwd.c exit.c)\



OBJ_PATH	=	./bin/

OBJS		=	$(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

CC			=	cc

# CFLAGS		=	-Wall -Werror -Wextra -g3 -fsanitize=address
CFLAGS		=	-Wall -Wextra -Werror

NAME		=	minishell

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
				@printf "\033[94m.\033[0m"
				@mkdir -p $(OBJ_PATH)
				@mkdir -p $(OBJ_PATH)/parsing
				@mkdir -p $(OBJ_PATH)/exec/lib
				@mkdir -p $(OBJ_PATH)/exec/builtin
				@$(CC) $(CFLAGS) -c $< -o $@ $(HEADER_INC) -I$(LIBFT_PATH) $(RL_INC)


$(NAME):		$(OBJS)
				@echo "\033[94m\n\nObject files has been compiled! \033[0m"
				@echo "\033[96m\nCompile libft ...\033[0m"
				@make -C $(LIBFT_PATH)
				@echo "\033[95m\nGenerating executable on $(OS_NAME) ...\033[0m"
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -lreadline $(RL_LIB) 
				@echo "\033[92m\n$(NAME) for $(OS_NAME) has been created! \033[0m"

all:			$(NAME)

clean:
				@rm -rf $(OBJ_PATH)
				@make -C $(LIBFT_PATH) fclean
				@echo "\033[91m\nObject files has been removed.\033[0m"

fclean:			clean
				@rm -f $(NAME)
				@echo "\033[91m\nExecutable file has been removed.\n\033[0m"

re: 			fclean all


.PHONY:			all clean fclean re bonus
