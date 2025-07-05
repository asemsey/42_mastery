
NAME		= ft_ls

CFLAGS		= -Wall -Wextra -Werror

SRCS		= src/main.c
OBJS		= ${SRCS:.c=.o}

LIBFT_URL	= https://github.com/asemsey/42_libft.git
LIBFT_PATH	= ./libft
LIBFT		= $(LIBFT_PATH)/libft.a
HEADERS		= -I ./include -I $(LIBFT_PATH)/include

# MLX_FLAGS	= 
# LIB_PATH	= ./lib
# LIB			= $(LIB_PATH)/full_libft.a

all: $(LIBFT) $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) $(LIBFT) -o $(NAME)
	@printf "Compiled successfully\nRun with:   ./ft_ls [flags]\n"

$(LIBFT):
	@if [ ! -d "$(LIBFT)" ]; then \
		git clone $(LIBFT_URL) $(LIBFT_PATH); \
	fi
	cd MLX42 && cmake -B build && cmake --build build

# $(LIB):
# 	@make -sC $(LIB_PATH)

clean:
	@rm -rf $(OBJS)
	@make -sC $(LIBFT_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)
	@make -sC $(LIBFT_PATH) fclean

re: clean all

.PHONY: all, clean, fclean, re