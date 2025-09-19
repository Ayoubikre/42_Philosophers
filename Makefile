CC = cc

CFLAGS = -Wall
# CFLAGS = -Wall -Werror -Wextra

PATH = ./philo
SRC = $(PATH)/main.c \
      $(PATH)/init.c \
      $(PATH)/routin.c \
      $(PATH)/action.c \
      $(PATH)/monitor.c \
      $(PATH)/utils.c

OBJC = $(SRC:%.c=%.o)
NAME = $(PATH)/philo


PATH_B = ./philo_bonus
SRC_B = $(PATH_B)/main_bonus.c \
#      $(PATH_B)/ \

OBJC_B = $(SRC_B:%.c=%.o)
NAME_B = $(PATH_B)/philo_bonus

all: $(NAME) 

$(NAME): $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) -o $(NAME)

$(PATH)/%.o: $(PATH)/%.c $(PATH)/main.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_B) 

$(NAME_B): $(OBJC_B)
	$(CC) $(CFLAGS) $(OBJC_B) -o $(NAME_B)

$(PATH_B)/%.o: $(PATH_B)/%.c $(PATH_B)/main_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJC) $(OBJC_B)

fclean: clean
	rm -f $(NAME) $(NAME_B)

re: fclean all

.phony: all clean fclean re bonus
