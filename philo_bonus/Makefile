CC = cc

CFLAGS = -Wall
# CFLAGS = -Wall -Werror -Wextra

SRC = main_bonus.c \
      init_bonus.c \
      utils_bonus.c \
      routin_bonus.c \

OBJC = $(SRC:%.c=%.o)
NAME = philo_bonus

all: clean $(NAME) 

$(NAME): $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) -o $(NAME) && echo && ./$(NAME) 3 100 50 40 

%.o: %.c main_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJC)

fclean: clean
	rm -f $(NAME)

re: fclean all

.phony: all clean fclean re
