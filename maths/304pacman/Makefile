##
## EPITECH PROJECT, 2018
## 301dannon
## File description:
## makefile
##

CC	=	g++

RM	=	rm -f

SRC	=	src/

SRCS	=	$(SRC)main.cpp  \
                $(SRC)Map.cpp   \
                $(SRC)Cell.cpp

OBJ	=	$(SRCS:.cpp=.o)

NAME	=	304pacman

CXXFLAGS	+=	-Wall -Wextra -I./include -std=c++14 -g

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ:.cpp=.cpp~)
	$(RM) $(OBJ:.cpp=.cpp#)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

c:	re
	$(RM) $(OBJ)

.PHONY: all clean fclean re
