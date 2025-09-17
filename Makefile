CC = cc
CFLAGS = -Wall
# CFLAGS = -Wall -Werror -Wextra

SRC = main.c init.c utils.c routin3.c
OBJC = $(SRC:%.c=%.o)

NAME = philo

all: clean $(NAME) 

$(NAME): $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) -o $(NAME) && echo && ./$(NAME) 4 01 100 1

%.o: %.c main.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJC) 

fclean: clean
	rm -rf $(NAME)

re: fclean all

.phony: all clean fclean re
