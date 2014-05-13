##
## Makefile for Makefile in /home/remi/Projet/PSU_2013_malloc
## 
## Made by remi
## Login   <remi@epitech.net>
## 
## Started on  Mon Feb  3 14:05:27 2014 remi
## Last update Tue May 13 14:22:37 2014 Maxime
##

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
