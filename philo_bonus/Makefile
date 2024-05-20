CFLAGS = -Wall -Wextra -Werror# -fsanitize=thread -g
NAME = philo_bonus
SRC =	main_bonus.c \
		convert_int_bonus.c \
		set_default_bonus.c \
		thread_managment_bonus.c \
		routine_bonus.c
 
GRN = "\033[32m"
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
# @echo $(GRN)DONE$(END)

clean:
	@echo $(RED)Remove [$(OSRC)$(BOSRC)]$(END)
	@rm -f $(OSRC) $(BOSRC)

fclean: clean
	@echo $(RED)Remove [$(NAME)$(BNAME)]$(END)
	@rm -f $(NAME) $(BNAME)

re: fclean all

.PHONY: clean