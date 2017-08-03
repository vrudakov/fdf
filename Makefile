NAME = fdf
SRC = draw.c get_next_line.c read.c ft_atoi_base.c ft_newsplit.c rotation.c main.c
FLAG = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit
OBJ = $(subst .c, .o, $(SRC))

all: compile

compile:
	make -C libft/
	gcc $(FLAG) -o $(NAME) $(SRC) libft/libft.a

clean:
	make clean -C libft/
	rm -f $(OBJ)

fclean:clean
	make fclean -C libft/
	rm -f $(NAME)

re:	fclean all
