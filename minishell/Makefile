.DEFAULT_GOAL := all

NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

SRCS = main.c utils.c error.c \
bnf_tree.c bnf_tree_utils1.c bnf_tree_utils2.c bnf_tree_utils3.c\
tokenize.c tokenize_utils1.c tokenize_utils2.c tokenize_utils3.c tokenize_utils4.c tokenize_utils5.c\
vector.c signal.c signal_utils.c signal_utils2.c\
./builtin/builtin_cd.c ./builtin/builtin_echo.c ./builtin/builtin_env.c ./builtin/builtin_exit.c ./builtin/builtin_export.c ./builtin/builtin_pwd.c ./builtin/builtin_unset.c \
./dictionary/dict_insert_remove.c ./dictionary/dict_make_utils.c ./dictionary/dict_make.c \
./execute/exec_cmdlst_maker.c ./execute/exec_cmdlst_utils.c ./execute/exec.c ./execute/exec_utils.c ./execute/exec_utils2.c ./execute/exec_utils3.c ./execute/exec_cmd_utils.c \
./execute/exec_cmd.c ./execute/exec_and_or.c ./execute/here_doc.c ./execute/here_doc_utils.c ./execute/here_doc_utils2.c ./execute/expansion.c ./execute/expansion_utils.c ./execute/ms_split.c \
./wildcard.c ./wildcard_utils.c ./wildcard_utils2.c ./wildcard_utils3.c

SRCS_LIB = $(SUB_LIBDIR)/ft_isalpha.c $(SUB_LIBDIR)/ft_isdigit.c $(SUB_LIBDIR)/ft_isalnum.c $(SUB_LIBDIR)/ft_isascii.c \
$(SUB_LIBDIR)/ft_isprint.c $(SUB_LIBDIR)/ft_strlen.c $(SUB_LIBDIR)/ft_memset.c $(SUB_LIBDIR)/ft_bzero.c \
$(SUB_LIBDIR)/ft_memcpy.c $(SUB_LIBDIR)/ft_memmove.c $(SUB_LIBDIR)/ft_strlcpy.c $(SUB_LIBDIR)/ft_strlcat.c \
$(SUB_LIBDIR)/ft_toupper.c $(SUB_LIBDIR)/ft_tolower.c $(SUB_LIBDIR)/ft_strchr.c $(SUB_LIBDIR)/ft_strrchr.c \
$(SUB_LIBDIR)/ft_strncmp.c $(SUB_LIBDIR)/ft_memchr.c $(SUB_LIBDIR)/ft_memcmp.c $(SUB_LIBDIR)/ft_strnstr.c \
$(SUB_LIBDIR)/ft_atoi.c $(SUB_LIBDIR)/ft_calloc.c $(SUB_LIBDIR)/ft_strdup.c $(SUB_LIBDIR)/ft_substr.c \
$(SUB_LIBDIR)/ft_strjoin.c $(SUB_LIBDIR)/ft_strtrim.c $(SUB_LIBDIR)/ft_split.c $(SUB_LIBDIR)/ft_itoa.c \
$(SUB_LIBDIR)/ft_strmapi.c $(SUB_LIBDIR)/ft_striteri.c $(SUB_LIBDIR)/ft_putchar_fd.c $(SUB_LIBDIR)/ft_putstr_fd.c \
$(SUB_LIBDIR)/ft_putendl_fd.c $(SUB_LIBDIR)/ft_putnbr_fd.c $(SUB_LIBDIR)/ft_lstnew.c $(SUB_LIBDIR)/ft_lstadd_front.c \
$(SUB_LIBDIR)/ft_lstsize.c $(SUB_LIBDIR)/ft_lstlast.c $(SUB_LIBDIR)/ft_lstadd_back.c $(SUB_LIBDIR)/ft_lstdelone.c \
$(SUB_LIBDIR)/ft_lstclear.c $(SUB_LIBDIR)/ft_lstiter.c $(SUB_LIBDIR)/ft_lstmap.c 

SUB_LIB = libft.a
SUB_LIBDIR = ./libft

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(SUB_LIBDIR)/$(SUB_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(SUB_LIBDIR) $(SUB_LIBDIR)/$(SUB_LIB) -lreadline

$(SUB_LIBDIR)/$(SUB_LIB) : $(SRCS_LIB)
	make -C $(SUB_LIBDIR)

%.o	: %.c
	$(CC) $(CFLAGS)  -c -o $@ $<

clean:
	make -C $(SUB_LIBDIR) clean
	$(RM) $(OBJS) $(BNS_OBJS)

fclean: clean
	make -C $(SUB_LIBDIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
