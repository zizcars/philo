CFLAGS = -Wall -Wextra -Werror -pthread
NAME = philo_bonus
SRC =	main_bonus.c \
		philo_tooles_bonus.c \
		set_default_bonus.c \
		thread_managment_bonus.c \
		routine_bonus.c
 
ORG = "\033[34m"
RED = "\033[31m"
END = "\033[0m"

OSRC=$(SRC:.c=.o)

%.o: %.c philo_bonus.h
	@echo $(ORG)Compiling [$@]...$(END)
	@cc $(CFLAGS) -c -o $@ $<


all: $(NAME)

$(NAME): $(OSRC) 
	@cc $(CFLAGS) $(OSRC) -o $(NAME)

clean:
	@echo $(RED)Remove [$(OSRC)$(BOSRC)]$(END)
	@rm -f $(OSRC) $(BOSRC)

fclean: clean
	@echo $(RED)Remove [$(NAME)$(BNAME)]$(END)
	@rm -f $(NAME) $(BNAME)

re: fclean all

.PHONY: clean