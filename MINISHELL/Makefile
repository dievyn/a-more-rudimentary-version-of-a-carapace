
NAME = ./minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 

OBJET = $(SRC:.c=.o)

SRC = parsing/fonction_annexes.c	\
	parsing/list.c					\
	parsing/random.c				\
	parsing/copy_args.c				\
	parsing/clean_args.c			\
	parsing/split_word.c			\
	parsing/split_word2.c			\
	parsing/split_cmd.c				\
	parsing/syntaxerror.c			\
	parsing/syntaxerror2.c			\
	parsing/unquote.c				\
	parsing/get_env_var.c			\
	pipex_flemme/pipex.c			\
	pipex_flemme/check_path.c		\
	pipex_flemme/utils.c			\
	pipex_flemme/make_dup.c			\
	pipex_flemme/make_dup2.c		\
	pipex_flemme/open_files.c		\
	pipex_flemme/open_files2.c		\
	pipex_flemme/exec.c				\
	pipex_flemme/exec2.c			\
	pipex_flemme/free_related.c		\
	pipex_flemme/free_related2.c	\
	built_in/built_in.c				\
	built_in/export.c				\
	built_in/export2.c				\
	built_in/ft_unset.c				\
	built_in/ft_cd.c				\
	built_in/echo.c					\
	built_in/ft_exit.c				\
	built_in/ft_pwd.c				\
	built_in/hex.c					\
	main.c							\
	signals.c						\
	random.c						\
	big_ft/ft_itoa.c				\
	big_ft/ft_atoi.c				\
	big_ft/ft_bzero.c				\
	big_ft/ft_split.c				\
	big_ft/ft_memcmp.c				\
	big_ft/ft_memchr.c				\
	big_ft/ft_memcpy.c				\
	big_ft/ft_memset.c				\
	big_ft/ft_strchr.c				\
	big_ft/ft_strlen.c				\
	big_ft/ft_calloc.c				\
	big_ft/ft_substr.c				\
	big_ft/ft_strdup.c				\
	big_ft/ft_strlcat.c				\
	big_ft/ft_isalnum.c				\
	big_ft/ft_isalpha.c				\
	big_ft/ft_isascii.c				\
	big_ft/ft_isdigit.c				\
	big_ft/ft_isprint.c				\
	big_ft/ft_strncmp.c				\
	big_ft/ft_strnstr.c				\
	big_ft/ft_strrchr.c				\
	big_ft/ft_tolower.c				\
	big_ft/ft_toupper.c				\
	big_ft/ft_strtrim.c				\
	big_ft/ft_memmove.c				\
	big_ft/ft_strjoin.c				\
	big_ft/ft_strlcpy.c				\
	big_ft/ft_strmapi.c				\
	big_ft/ft_striteri.c			\
	big_ft/ft_putnbr_fd.c			\
	big_ft/ft_putstr_fd.c			\
	big_ft/ft_putchar_fd.c			\
	big_ft/ft_putendl_fd.c			\
	big_ft/printf_ex/ft_printf.c	\
	big_ft/printf_ex/put_x.c		\
	big_ft/printf_ex/put_x2.c

all: $(NAME)

$(NAME): $(OBJET)
	$(CC) $(CFLAGS) $(OBJET) -o $(NAME) -lreadline

test : $(OBJET)
	echo

clean:
	rm -f $(OBJET) ./minishell

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
