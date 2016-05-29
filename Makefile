NAME = nm-otool

C_DIR =	srcs
C_DIRS = $(shell find $(C_DIR) -type d -follow -print)
C_FILES = $(shell find $(C_DIR) -type f -follow -print | grep "\.c")

O_DIR =	.tmp/obj
O_DIRS = $(C_DIRS:$(C_DIR)%=$(O_DIR)%)
O_FILES = $(C_FILES:$(C_DIR)%.c=$(O_DIR)%.o)

FLAGS = -Wall -Wextra -Werror
INCLUDES = -Iincludes -Ilibft/includes
LIB = -Llibft -lft

all: $(NAME)

$(NAME): $(O_FILES)
	make -C libft
	gcc $(FLAGS) $^ $(LIB) $(SRCI) -o $@

$(O_DIR)%.o: $(C_DIR)%.c
	mkdir -p $(O_DIRS) $(O_DIR)
	gcc $(FLAGS) $(INCLUDES) -o $@ -c $&lt;

clean:
	make clean -C libft
	rm -rf $(O_DIR)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)
	rm -rf .tmp/

re: fclean all

.PHONY: clean all fclean re
