CFLAGS = -Wall -Wextra -Werror # -fsanitize=thread -g
NAME = philo_bonus

BSRC=	main_bonus.c  \
		set_default_bonus.c \
		philo_tooles_bonus.c \
		manage_forks_bonus.c \
		routine_bonus.c

OSRC=$(BSRC:.c=.o)

all : $(NAME)

$(NAME): $(OSRC) philo_bonus.h
	cc $(CFLAGS) $(OSRC) -o $(NAME)

clean:
	rm -f $(OSRC)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean