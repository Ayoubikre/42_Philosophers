CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC = main.c
OBJC = $(SRC:%.c=%.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) -o $(NAME)

%.o: %.c main.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJC) 

fclean: clean
	rm -rf $(NAME)

re: fclean all

.phony: all clean fclean re