CC = cc

CFLAGS = -Wall
CFLAGS = -Wall -Werror -Wextra

SRC = ./Mandatory/main.c \
      ./Mandatory/init.c \
      ./Mandatory/routin.c \
      ./Mandatory/action.c \
      ./Mandatory/monitor.c \
      ./Mandatory/utils.c

OBJC = $(SRC:%.c=%.o)
NAME = philo


SRC_B = Bonus/main_bonus.c \
#      Bonus/ \

OBJC_B = $(SRC_B:%.c=%.o)
NAME_B = philo_bonus

all: $(NAME) 

$(NAME): $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) -o $(NAME)

./Mandatory/%.o: ./Mandatory/%.c ./Mandatory/main.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_B) 

$(NAME_B): $(OBJC_B)
	$(CC) $(CFLAGS) $(OBJC_B) -o $(NAME_B)

Bonus/%.o: Bonus/%.c Bonus/main_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJC) $(OBJC_B)

fclean: clean
	rm -f $(NAME) $(NAME_B)

re: fclean all

.phony: all clean fclean re bonus
