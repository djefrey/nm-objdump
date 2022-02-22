##
## EPITECH PROJECT, 2020
## libmy
## File description:
## first makefile
##

LIST_SRC	=	$(wildcard ./my_list/*.c)

INC_DIR		=	../include/

CFLAGS		=	-I$(INC_DIR) -W -Wall

OBJ			=	$(LIST_SRC:.c=.o)

NAME		=	libmy.a

all:	$(NAME)

$(NAME):	$(OBJ)
	ar -crs $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re: fclean all
