CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRC =	main.c \
		philo_tooles.c

OSRC=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OSRC)
	cc $(CFLAGS) $(OSRC) -o $(NAME)

clean:
	rm -f $(OSRC)
fclean: clean
	rm -f $(NAME)

re: fclean all
