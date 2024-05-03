CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRC =	main.c \
		philo_tooles.c \
		create_table.c \
		manage_forks.c

OSRC=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OSRC) philo.h
	cc $(CFLAGS) $(OSRC) -o $(NAME)

clean:
	rm -f $(OSRC)

fclean: clean
	rm -f $(NAME)

re: fclean all
