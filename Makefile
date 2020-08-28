NAME = rtv1
LIB_FLAGS = -Wall -Wextra
FLAGS = -I SDL2.framework/Headers -F ./ -framework SDL2
LIBRARY = ./libft/libft.a
HEADER = rtv1.h
SRC = main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ): %.o: %.c
		gcc -c $(LIB_FLAGS) -I libft/ -o $@ $<

$(LIBRARY):
		@make -C libft/

$(NAME): $(LIBRARY) $(OBJ)
		@cp -r SDL2.framework ~/Library/Frameworks/
		@gcc $(OBJ) $(LIBRARY) -o $(NAME) $(FLAGS) -I $(HEADER)

clean:
	@rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf ~/Library/Frameworks/SDL2.framework
	@make -C libft fclean

re: fclean all
