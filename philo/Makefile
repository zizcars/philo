CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRC =	main.c \
		convert_int.c \
		set_default.c \
		thread_managment.c \
		routine.c \
		philo_tooles.c
 
ORG = "\033[34m"
RED = "\033[31m"
END = "\033[0m"

OSRC=$(SRC:.c=.o)

%.o: %.c philo.h
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