CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g
NAME = philo
SRC =	main.c \
		convert_int.c \
		set_default_values.c \
		manage_threads.c \
		routine.c 

OSRC=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OSRC) philo.h
	cc $(CFLAGS) $(OSRC) -o $(NAME)

clean:
	rm -f $(OSRC) $(BOSRC)

fclean: clean
	rm -f $(NAME) $(BNAME)

re: fclean all

.PHONY: clean