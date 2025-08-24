# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/20 11:11:03 by nkiefer           #+#    #+#              #
#    Updated: 2025/07/14 18:15:05 by nkiefer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalpha.c \
       ft_isdigit.c \
       ft_isalnum.c \
       ft_isprint.c \
       ft_strlen.c \
       ft_memset.c \
       ft_bzero.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_strlcpy.c \
       ft_strlcat.c \
       ft_toupper.c \
       ft_tolower.c \
       ft_strchr.c \
       ft_strrchr.c \
       ft_strncmp.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_strnstr.c \
       ft_calloc.c \
       ft_atoi.c \
       ft_striteri.c \
       ft_putchar_fd.c \
       ft_putstr_fd.c \
       ft_putendl_fd.c \
       ft_putnbr_fd.c \
       ft_strmapi.c \
       ft_itoa.c \
       ft_strdup.c \
       ft_isascii.c \
       ft_strtrim.c \
       ft_substr.c \
       ft_strjoin.c \
       ft_split.c \
       ft_atol.c \
       ft_isspace.c \
       ft_swap.c \
       ft_strcmp.c \
       ft_strcspn.c \
       ft_strcpy.c \
       ft_strndup.c \
       ft_strncpy.c \
       ft_bubble_str_sort.c \
       GNL/get_next_line.c \
       GNL/get_next_line_utils.c \
       GNL/get_next_line_utils.c \
       PRINTF/ft_printf.c \
       PRINTF/ft_print_num.c \
       PRINTF/ft_print_pointer.c \
       PRINTF/ft_print_f.c \


OBJS = ${SRCS:.c=.o}
CC = cc
RM = rm -f
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}
	
${NAME}: ${OBJS}
	$(AR) $@ $^
	
%.o: %.c	
	${CC} ${CFLAGS} -c $< -o $@

clean: 
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re so
