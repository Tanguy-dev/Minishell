.PHONY: libft

MAIN		=	minishell signal
PARSE		=	parse parse2 parse3 parse4 token token2 redir expansion expansion2
ENV			=	env env_sort get_env
UTILS		=	free type fd strchr_ret
EXEC		=	bin bin2 exec builtins
BUILTINS	=	echo cd cd_2 pwd export export2 export3 env exit unset unset2
READL_PATH	=	-L$(shell brew --prefix readline)/lib

SRCS		=	$(addsuffix .c, $(addprefix main/, $(MAIN)))	\
				$(addsuffix .c, $(addprefix parsing/, $(PARSE)))	\
				$(addsuffix .c, $(addprefix env/, $(ENV)))	\
				$(addsuffix .c, $(addprefix utils/, $(UTILS)))	\
				$(addsuffix .c, $(addprefix exec/, $(EXEC)))	\
				$(addsuffix .c, $(addprefix builtins/, $(BUILTINS)))	\

OBJS	=	$(addprefix srcs/, $(SRCS:.c=.o))

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I includes
NAME	=	minishell

%.o: %.c
		@printf "\033[0;34mGenerating minishell : %-33.33s\r" $@
		@${CC} ${CFLAGS} -c $< -o $@

all:	 libft $(NAME)

libft:
		@make -C libft/

$(NAME):	$(OBJS)
		@$(CC) -fsanitize=address -o $@ $^ -Llibft -lft $(READL_PATH) -lreadline
		@echo "\n\n\033[0;32mCompiling minishell"

clean: 
		@rm -f $(OBJS)
		@make -C libft clean

fclean:	clean
		@rm -f $(NAME)
		@make -C libft fclean

re:		fclean all
