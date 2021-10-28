NAME		=	cub3d

INCLUDE_DIR	=	inc

HEADER		=	$(INCLUDE_DIR)/cub3d.h

SRC_DIR		=	src/cub3d

SRCS		=	$(SRC_DIR)/parse.c				\
				$(SRC_DIR)/service.c			\
				$(SRC_DIR)/elem_func_color.c	\
				$(SRC_DIR)/elem_func_texture.c	\
				$(SRC_DIR)/parse_map.c			\
				$(SRC_DIR)/parse_elem.c			\
				$(SRC_DIR)/parse_map_check.c	\
				$(SRC_DIR)/main.c
				

OBJS_DIR	=	objects/cub3d/

# MLX_FLAGS	=	-framework OpenGL -framework AppKit -lmlx

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

OBJS		=	$(addprefix $(OBJS_DIR), $(SRCS:c=o))

LIBFT_DIR	=	src/libft

LIBFT		=	libft.a

GNL_DIR		=	src/gnl

GNL			=	libgnl.a

# MLX_DIR		=	src/mlx

# MLX			=	libmlx.a


$(OBJS_DIR)%.o:		%.c $(HEADER)
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE_DIR)

all:				$(NAME)

$(GNL):
					@make -C $(GNL_DIR)

$(LIBFT):
					@make -C $(LIBFT_DIR)


# $(MLX):
# 					@make -C $(MLX_DIR)

$(NAME):			$(GNL) $(LIBFT) $(OBJS) $(HEADER)# $(MLX)
					@$(CC) $(OBJS) -I $(INCLUDE_DIR) -lft -lgnl -L. -o $(NAME)

clean:
					@make clean -C $(LIBFT_DIR)
					@make clean -C $(GNL_DIR)
					@$(RM) $(OBJS)

fclean: 			clean
					@make fclean -C $(LIBFT_DIR)
					@make fclean -C $(GNL_DIR)
					@$(RM) $(NAME)

re: 				clean all

.PHONY: 			all clean fclean re