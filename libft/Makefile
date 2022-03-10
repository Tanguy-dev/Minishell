# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thamon <thamon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 15:36:54 by thamon            #+#    #+#              #
#    Updated: 2022/03/04 20:24:44 by thamon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CONV = ft_atoi ft_itoa
IS = ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint
LST = ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone ft_lstiter ft_lstlast ft_lstnew
MATH = ft_abs ft_baselen ft_nbrlen ft_power ft_sqrt
MEM = ft_bzero ft_calloc ft_memccpy ft_memdel ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset
PUT = ft_putchar_fd ft_putchar ft_putendl_fd ft_putendl ft_putnbr_base ft_putnbr_fd ft_putnbr ft_putstr_fd ft_putstr
STR = ft_split ft_strcapitalize ft_strcat ft_strchr ft_strcmp ft_strcpy ft_strdup ft_strjoin ft_strlcat ft_strlcpy ft_strlen ft_strlowcase ft_strmapi ft_strncat ft_strncmp ft_strncpy ft_strnstr ft_strrchr ft_strstr ft_strtrim ft_substr ft_strisnum ft_strarraylen
TO = ft_tolower ft_toupper
SKIP = space spacenl

SRC = $(addsuffix .c, $(addprefix ft_conv/, $(CONV))) \
	$(addsuffix .c, $(addprefix ft_is/, $(IS))) \
	$(addsuffix .c, $(addprefix ft_lst/, $(LST))) \
	$(addsuffix .c, $(addprefix ft_math/, $(MATH))) \
	$(addsuffix .c, $(addprefix ft_mem/, $(MEM))) \
	$(addsuffix .c, $(addprefix ft_put/, $(PUT))) \
	$(addsuffix .c, $(addprefix ft_str/, $(STR))) \
	$(addsuffix .c, $(addprefix ft_to/, $(TO))) \
	$(addsuffix .c, $(addprefix ft_skip/ft_skip_, $(SKIP))) \

OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -I includes/
CC = gcc
HEADER = $(addsuffix .h, $(addprefix includes/, libft get_next_line))


all: $(NAME)

$(NAME): ${OBJS}
		@echo "\n\n\033[0;32mCompiling libft"
		@ar rc $(NAME) $^
		@ranlib $(NAME)
		@echo "\033[0m"

%.o: %.c
		@printf "\033[0;34mGenerating libft : %-33.33s\r" $@
		@${CC} ${CFLAGS} -c $< -o $@

clean:
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re: 	fclean all

.PHONY : all clean fclean re