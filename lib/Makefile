SRC		=	test.c		\

OBJ		=	$(SRC:.c=.o)

CFLAGS		=	-I./include/

LDFLAGS		=	-L./lib/ -llua5.1

NAME		=	test

$(NAME):		$(OBJ)
			gcc -o $(NAME) $(OBJ) $(LDFLAGS)

all:			$(NAME)

clean:
			rm -f $(OBJ)

fclean:			clean
			rm -f $(NAME)

re:			fclean all
