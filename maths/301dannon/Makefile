##
## EPITECH PROJECT, 2018
## 301dannon
## File description:
## makefile
##

CC	=	g++

RM	=	rm -f

SRC	=	src/

SRCS	=	$(SRC)main.cpp 		\
		$(SRC)Sorter.cpp 	\
		$(SRC)BubbleSort.cpp	\
		$(SRC)InsertionSort.cpp	\
		$(SRC)SelectSort.cpp	\
		$(SRC)QuickSort.cpp	\
		$(SRC)FusionSort.cpp	\
		$(SRC)ListFactory.cpp

OBJ	=	$(SRCS:.cpp=.o)

NAME	=	301dannon

CXXFLAGS	+=	-Wall -Wextra -Werror -I./include -std=c++11

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
