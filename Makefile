DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all bonus clean fclean re

#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -I./include 
RM		=	rm -f
MAKE	=	make

# Output file name
NAME	=	cub3d

# Sources are all .c files
SRCS =	main.c\
		init.c \
		move.c \
		loop.c \
		raycasting.c \
		raycasting2.c \
		utils.c \
		parsing.c

SRCS_DIR	=	src

# Objects are all .o files
OBJS_DIR	=	bin
OBJS	:= 	$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

# Library
LIBFT	=	libft/libft.a
MLX_GIT	=	https://github.com/codam-coding-college/MLX42.git
MLX42	=	MLX42/build/libmlx42.a
MLX_FLAG	=	-framework Cocoa -framework OpenGL -framework IOKit $(MLX42) -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

# Colors
GREEN	=	\033[38;5;46m
LIME	=	\033[0;92m
RESET	=	\033[0m

MAP	=	./map/map2.cub	
$(shell mkdir -p $(OBJS_DIR))
#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: $(NAME) 
	

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -MMD

# Generates output file
$(NAME): $(OBJS) $(LIBFT) $(MLX42) 
	$(CC) $(CFLAGS) $(LIBFT) $(MLX_FLAG) -o $@ $^
	
# Compiles sources into objects

$(LIBFT):
	$(MAKE) -C libft
# Removes objects
clean:
	$(HIDE)$(RM) $(OBJS) $(OBJS:.o=.d) 

# Removes objects and executables
fclean: clean
	$(HIDE)$(RM) $(NAME)
	$(MAKE) -C libft fclean
	
# Removes objects and executables and remakes
re: fclean all

run: $(NAME)
	./$(NAME) $(MAP)

leaks: $(NAME)
	leaks -atExit -- ./$(NAME) $(MAP)
	
mlx:
	git clone $(MLX_GIT)
	cd MLX42 && cmake -B build
	cd MLX42 && cmake --build build -j4

-include $(OBJS:.o=.d)