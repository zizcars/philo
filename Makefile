CFLAGS = -Wall -Wextra -Werror # -fsanitize=thread -g
NAME = philo
SRC =	main.c \
		philo_tooles.c \
		create_table.c \
		manage_forks.c \
		routine.c 

OSRC=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OSRC) philo.h
	cc $(CFLAGS) $(OSRC) -o $(NAME)

clean:
	rm -f $(OSRC)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean