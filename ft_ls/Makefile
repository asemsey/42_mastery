
NAME		= ft_ls

CFLAGS		= -Wall -Wextra -Werror

SRCS		= main.c \
			filedata.c handle_args.c test_helpers.c \
			file_info.c directories.c format.c
OBJS		= ${SRCS:.c=.o}
OBJS		:= $(addprefix obj/, $(OBJS))
SRCS		:= $(addprefix src/, $(SRCS))

# LIBFT_URL	= https://github.com/asemsey/42_libft.git
LIBFT_PATH	= ./libft
LIBFT		= $(LIBFT_PATH)/libft.a
HEADERS		= -I ./include -I $(LIBFT_PATH)/libft.h

all: $(LIBFT) $(NAME)

obj/%.o: src/%.c
	@mkdir -p obj
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) $(LIBFT) -o $(NAME)
	@printf "Compiled successfully\nRun with:   ./ft_ls [option] [file/directory]\n"

$(LIBFT):
	@make -sC $(LIBFT_PATH) bonus

clean:
	@rm -rf $(OBJS)
	@make -sC $(LIBFT_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all, clean, fclean, re