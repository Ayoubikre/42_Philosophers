CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = main.c \
      init.c \
      routin.c \
      action.c \
      monitor.c \
      utils.c \

OBJC = $(SRC:%.c=%.o)
NAME = philo

all: $(NAME) 

$(NAME): $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) -o $(NAME)

%.o: %.c main.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJC)

fclean: clean
	rm -f $(NAME)

re: fclean all

.phony: all clean fclean re
