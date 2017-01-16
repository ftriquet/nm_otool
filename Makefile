NM_SRCS_NAMES = nm/nm.c \
				nm/section.c \
				nm/section_32.c \
				nm/symbol_table.c \
				nm/symbols.c \
				nm/symbols_32.c \
				nm/symlist.c \
				nm/fat.c \
			   	nm/sort.c \
				nm/main.c

NM_OBJS_NAMES = $(NM_SRCS_NAMES:.c=.o)

OTOOL_SRCS_NAMES = otool/ft_otool.c \
				   # ft_otool_d.c \
				   # ft_otool_tmp.c

OTOOL_OBJS_NAMES = $(OTOOL_SRCS_NAMES:.c=.o)

SRC_DIR = src/

OBJ_DIR = obj/

NM_SRCS = $(addprefix $(SRC_DIR), $(NM_SRCS_NAMES))
OTOOL_SRCS = $(addprefix $(SRC_DIR), $(OTOOL_SRCS_NAMES))

NM_OBJS = $(addprefix $(OBJ_DIR), $(NM_OBJS_NAMES))
OTOOL_OBJS = $(addprefix $(OBJ_DIR), $(OTOOL_OBJS_NAMES))

CFLAGS = -Wall -Wextra -Werror -g

LDFLAGS = -lft -L libft

INCFLAGS = -I includes -I libft/includes

all: ft_nm ft_otool

ft_otool: $(OTOOL_OBJS)
	make -C libft
	gcc $(CLFAGS) $^ $(LDFLAGS) $(INCFLAGS) -o $@


ft_nm: $(NM_OBJS)
	make -C libft
	gcc $(CLFAGS) $^ $(LDFLAGS) $(INCFLAGS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR){nm,otool}
	gcc -c $(CFLAGS) $< -o $@ $(INCFLAGS)

clean:
	make clean -C libft
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C libft
	rm -f ft_nm ft_otool

re: fclean all

.PHONY: clean all fclean re
