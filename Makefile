CC = cc
CFLAGS = -Wall
# CFLAGS = -Wall -Werror -Wextra

SRC = main.c init.c utils.c routin.c
OBJC = $(SRC:%.c=%.o)

NAME = philo

all: clean $(NAME) 

$(NAME): $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) -o $(NAME) && echo && ./$(NAME) 5 300 100 100

%.o: %.c main.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJC) 

fclean: clean
	rm -rf $(NAME)

re: fclean all

.phony: all clean fclean re