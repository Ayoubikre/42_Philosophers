CC = cc

CFLAGS = -Wall
# CFLAGS = -Wall -Werror -Wextra

SRC = main_bonus.c \


OBJC = $(SRC:%.c=%.o)
NAME = philo

all: $(NAME) 

$(NAME): $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) -o $(NAME)

%.o: %.c main_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJC)

fclean: clean
	rm -f $(NAME)

re: fclean all

.phony: all clean fclean re
