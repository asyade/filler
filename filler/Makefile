CC = gcc

NAME = acorbeau.filler

PATH_SRC = srcs

DIRS =	obj

SRC = srcs/abs.c \
	  srcs/cells.c \
	  srcs/chunk.c \
	  srcs/debug.c \
	  srcs/distance.c \
	  srcs/filler.c \
	  srcs/parser.c \
	  srcs/place.c \
	  srcs/reset.c \
	  srcs/ft_xalloc.c \
	  srcs/ft_xmap.c \

OBJ = $(patsubst $(PATH_SRC)/%.c, obj/%.o, $(SRC))

FLAGS = -Wall -Wextra -Werror

LIBS = -L./libft -lft

HEADERS = -I includes/

.SILENT :

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft/
	$(CC) $(FLAGS) $(OBJ) libft/libft.a -o $(NAME) -I includes/
	echo "\033[33mCreating  \033[32m[✔] \033[0m$(NAME)"

obj/%.o : $(PATH_SRC)/%.c
	mkdir -p $(DIRS)
	$(CC) $(FLAGS) -c $< -o $@ -I includes/
	echo "\033[33mCompiling \033[32m[✔] \033[0m$<"

.PHONY : clean fclean

clean :
	make -C libft/ clean
	/bin/rm -rf obj/
	echo "\033[31mRemoving  \033[32m[✔] \033[0mObject files"

fclean : clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)
	echo "\033[31mRemoving  \033[32m[✔] \033[0m$(NAME)"

re : fclean all
