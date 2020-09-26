NAME = rtv1
NAME_LINUX = rtv1_linux
LIB_FLAGS = -Wall -Wextra
MAC_FLAGS = -I SDL2.framework/Headers -F ./ -framework SDL2
LINUX_FLAGS = -lSDL2 -lm
LIBRARY = ./libft/libft.a
HEADER = rtv1.h
SRC = main.c sphere.c settings.c vector.c utils.c \
	light.c triangle.c scenes_reader.c draw.c ftoi.c \
	objects_parameters.c plane.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ): %.o: %.c $(HEADER)
		gcc -c $(LIB_FLAGS) -I libft/ -o $@ $<

$(LIBRARY):
		@make -C libft/

$(NAME): $(LIBRARY) $(OBJ)
		@cp -r SDL2.framework ~/Library/Frameworks/
		@gcc $(OBJ) $(LIBRARY) -o $(NAME) $(MAC_FLAGS) -I $(HEADER)

linux: $(NAME_LINUX) 

$(OBJ): %.o: %.c $(HEADER)
	gcc -c $(LIB_FLAGS) -I libft/ -o $@ $<

$(LIBRARY):
		@make -C libft/

$(NAME_LINUX): $(LIBRARY) $(OBJ)
		@gcc $(OBJ) $(LIBRARY) -o $(NAME_LINUX) $(LINUX_FLAGS) -I $(HEADER)

clean:
	@rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf ~/Library/Frameworks/SDL2.framework
	@make -C libft fclean

fclean_linux: clean
	@rm -f $(NAME_LINUX)
	@make -C libft fclean

re: fclean all
