NAME	= philo

SOURCES	= \
	main.c \
	init.c \
	routine.c \
	start .c \
	utils.c \

OBJS	= $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re