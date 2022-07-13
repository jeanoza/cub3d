# this is to manage flags for m1 architecture, we don't have to use this flag in linux
OS_ARCH 	:= $(shell uname -m)
ifeq ($(OS_ARCH),arm64)
	MLX_PATH:= ./mlx_mac/
	MLX_LIB := -lmlx -framework OpenGL -framework AppKit
	OS_NAME := Mac M1
else
	MLX_PATH:= ./mlx_linux/
	MLX_LIB	:= -lmlx -lXext -lX11
	OS_NAME := Linux
endif

HEADER_INC	:=	-I./include

LIBFT_PATH	:=	./libft/

SRC_PATH	=	./src/

SRCS		=	main.c \
				painter.c \
				free.c \
				init.c \
				event.c \
				utils.c \
				$(addprefix parsing/, file_and_color.c heat_seeker.c heat_seeking.c parse.c putter.c parse_error.c check_map.c tokenize_map.c tokenize_map_help.c)\
				# $(addprefix exec/, )

OBJ_PATH	=	./bin/

OBJS		=	$(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra #-g3 -fsanitize=address

NAME		=	cub3D

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
				@printf "\033[94m.\033[0m"
				@mkdir -p $(OBJ_PATH)
				@mkdir -p $(OBJ_PATH)/parsing
				@$(CC) $(CFLAGS) -c $< -o $@ $(HEADER_INC) -I$(LIBFT_PATH) -I$(MLX_PATH)


$(NAME):		$(OBJS)
				@echo "\033[94m\n\nObject files has been compiled! \033[0m"
				@echo "\033[96m\nCompile libft ...\033[0m"
				@make -C $(LIBFT_PATH)
				@make -C $(MLX_PATH)
				@echo "\033[95m\nGenerating executable on $(OS_NAME) ...\033[0m"
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_PATH) -lft -L$(MLX_PATH) $(MLX_LIB)
				@echo "\033[92m\n$(NAME) for $(OS_NAME) has been created! \033[0m"

all:			$(NAME)

clean:
				@rm -rf $(OBJ_PATH)
				@make -C $(LIBFT_PATH) fclean
				@make -C $(MLX_PATH) clean
				@echo "\033[91m\nObject files has been removed.\033[0m"

fclean:			clean
				@rm -f $(NAME)
				@echo "\033[91m\nExecutable file has been removed.\n\033[0m"

re: 			fclean all


.PHONY:			all clean fclean re bonus
