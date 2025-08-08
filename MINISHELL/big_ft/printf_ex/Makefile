
NAME = libftprintf.a

CC = cc

AR = ar

CFLAGS = -Werror -Wall -Wextra

SRC = ft_printf.c \
	ft_putstr.c \
	ft_strnstr.c \
	ft_putnbr.c \
	ft_putnbru.c \
	ft_putchar.c \
	ft_hexaprintu.c \
	ft_hexaprintl.c \
	ft_print_adresse.c \

OBJET = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJET)
	$(AR) rcs $(NAME) $(OBJET)

#$(OBJET): $(SRC)
#	$(CC) $(CFLAGS) -c $< -o $@
	
test : $(OBJET)
	echo

clean:
	rm -f $(OBJET)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
