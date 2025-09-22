CC = cc

CFLAGS = -Wall -Werror -Wextra 

SRC = main_bonus.c \
      init_bonus.c \
      manager_bonus.c \
      action_bonus.c \
      utils_bonus.c \

OBJC = $(SRC:%.c=%.o)
NAME = philo_bonus

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
