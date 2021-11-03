NAME		=	cub3d

INCLUDE_DIR	=	inc/mandatory

INCS		=	render.h		\
				parse.h			\
				events.h		\
				draw.h			\
				draw_utils.h	\
				settings.h		\
				map.h			\
				event_utils.h	\
				utils.h			\
				init_r_data.h
				
HEADER		=	$(addprefix $(INCLUDE_DIR)/, $(INCS))

SRC_DIR		=	src/cub3d/mandatory

CFILES		=	parse.c				\
				service.c			\
				elem_func_color.c	\
				elem_func_texture.c	\
				parse_map.c			\
				parse_elem.c		\
				parse_map_check.c	\
				start.c				\
				init.c				\
				init_utils.c		\
				init_r_data.c		\
				cast.c				\
				cast_utils.c		\
				draw.c				\
				draw_utils.c		\
				events.c			\
				event_utils.c		\
				utils.c				\
				main.c

SRCS		=	$(addprefix $(SRC_DIR)/, $(CFILES))
				
OBJS_DIR	=	objects/cub3d/

MLX_FLAGS	=	-framework OpenGL -framework AppKit -lmlx

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror# -O3

RM			=	rm -f

OBJS		=	$(addprefix $(OBJS_DIR), $(SRCS:c=o))

LIBFT_DIR	=	src/libft

LIBFT		=	libft.a

GNL_DIR		=	src/gnl

GNL			=	libgnl.a

MLX_DIR		=	src/mlx

MLX			=	libmlx.a


$(OBJS_DIR)%.o:		%.c $(HEADER)
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE_DIR)

all:				$(NAME)

$(GNL):
					@make -C $(GNL_DIR)

$(LIBFT):
					@make -C $(LIBFT_DIR)

$(MLX):
					@make -C $(MLX_DIR)

$(NAME):			$(GNL) $(LIBFT) $(OBJS) $(HEADER) $(MLX)
					@$(CC) $(OBJS) -I $(INCLUDE_DIR) $(MLX_FLAGS) -lft -lgnl -L. -o $(NAME)

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
