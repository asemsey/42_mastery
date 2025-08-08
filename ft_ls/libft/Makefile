NAME = libft.a

CFLAGS = -Wall -Wextra -Werror
SRC_DIR = srcs
OBJ_DIR = obj

# ------------------------------------------------------------------------------------

_SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c\
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c\
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
_BSRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c\
	ft_lstpushin.c ft_lstpopout.c ft_lstswap.c ft_max.c\
	ft_getenv.c ft_putnbr_u.c ft_puthex.c ft_printf.c ft_put1.c ft_put2.c ft_digits.c
SRCS = $(addprefix $(SRC_DIR)/, $(_SRCS))
BSRCS = $(addprefix $(SRC_DIR)/, $(_BSRCS))

_OBJ = $(_SRCS:.c=.o)
_BOBJ = $(_BSRCS:.c=.o)
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))
BOBJ = $(patsubst %,$(OBJ_DIR)/%,$(_BOBJ))

# ------------------------------------------------------------------------------------

all:	$(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	mkdir -p $(OBJ_DIR)
	ar rcs $(NAME) $(OBJ)

bonus:	$(OBJ_DIR) $(OBJ) $(BOBJ)
	ar rcs $(NAME) $(OBJ) $(BOBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	cc $(CFLAGS) -c $< -o $@

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf $(OBJ_DIR)

re: fclean all
