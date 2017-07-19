make -C libft/ all;gcc -fsanitize=address srcs/*.c libft/libft.a -I includes/ -o acorbeau.filler -g3 -Wall -Wextra && cat basicinput | ./acorbeau.filler
