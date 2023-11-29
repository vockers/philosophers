NAME	= philo
CFLAGS	= -fsanitize=address

SOURCES	= \
	main.c \
	init.c \
	routine.c \
	start.c \
	utils.c \

OBJS	= $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re