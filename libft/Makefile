# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 19:54:24 by pbergero          #+#    #+#              #
#    Updated: 2023/10/22 18:11:39 by pbergero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all bonus clean fclean re 

#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Compiler and flags
CC      =   gcc
CFLAGS  =   -Wall -Werror -Wextra -I./include
RM      =   rm -f
LIBCMP  =   ar -rcs

# Output file name
NAME    =   libft.a
# Sources are all .c files
SRCS    =   ft_calloc.c ft_isalnum.c \
			ft_isalpha.c ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c ft_itoa.c \
			ft_memchr.c ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c ft_putchar_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c \
			ft_putstr_fd.c ft_split.c \
			ft_strchr.c ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c ft_strnstr.c \
			ft_strrchr.c ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c ft_toupper.c \
			ft_atoi.c ft_bzero.c \
			ft_memcmp.c\
			get_next_line.c\
			get_next_line_utils.c\
			free_double_array.c\
			square_power.c\
			write_error.c\
			str_is_int.c\
			ft_strcmp.c

SRCS_DIR    =   src
# Objects are all .o files
OBJS_DIR    =   bin
OBJS := $(SRCS:%.c=$(OBJS_DIR)/%.o)

#style points

GREEN   =   \033[38;5;46m
LIME    =   \033[0;92m
RESET   =   \033[0m

$(shell mkdir -p $(OBJS_DIR))
#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all:  $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -MMD

# Generates output file
$(NAME): $(OBJS)
	$(LIBCMP) $(NAME) $(OBJS) $(INC)

# Compiles sources into objects

# Removes objects
clean:
	$(HIDE)$(RM) $(OBJS)  $(OBJS:.o=.d)

# Removes objects and executables
fclean: clean
	$(HIDE)$(RM) $(NAME)
	
# Removes objects and executables and remakes
re: fclean all

-include $(OBJS:.o=.d)
