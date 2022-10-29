NAME = minishell

LIBFT = include/libft/libft.a
LIBFT_PATH = include/libft/
READLINE = include/readline/libreadline.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
RM = rm -f
RLFLAGS = -lreadline -lncurses 

BUILTINS = echo 
ENV = env 
EXECUTE = execution
MAIN = minishell init
PARSING = parsing
UTILS = utils logs

SRCS = $(addsuffix .c, $(addprefix src/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix src/env/, $(ENV))) \
	  $(addsuffix .c, $(addprefix src/execute/, $(EXECUTE))) \
	  $(addsuffix .c, $(addprefix src/main/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix src/parsing/, $(PARSING))) \
	  $(addsuffix .c, $(addprefix src/utils/, $(UTILS))) \

OBJS = $(SRCS:c=o)

all: 	$(NAME)
	@echo "BOOM 💥💥💥💥💥 $(NAME) Compiled! 💯 $(DEFAULT)"


$(NAME): $(OBJS)
	-@$(MAKE) -C $(LIBFT_PATH)
	-@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(READLINE) $(RLFLAGS)
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
	@$(RM) $(OBJS)
	@make -C $(LIBFT_PATH) clean
	@echo "$(YELLOW)Object files deleted!$(DEFAULT)💯"

fclean:	clean
	@$(RM) $(NAME) $(LIBFT)

re:		fclean all

.PHONY:	all clean libft fclean re
git:
	@git add .
	@read -p "tag? : " TAG && git commit -m "$$TAG"
	@git push
	@echo "\n$(PURPLE)$(NAME) Committed!$(DEFAULT)💯"

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
PURPLE = \033[1;35m



