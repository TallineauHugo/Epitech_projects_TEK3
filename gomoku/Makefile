##
## EPITECH PROJECT, 2018
## 301dannon
## File description:
## makefile
##

CC	=	g++

RM	=	rm -f

SRC	=	srcs/

SRCS	=	$(SRC)main.cpp		\
		$(SRC)Listener.cpp	\
		$(SRC)AI.cpp		\
		$(SRC)Board.cpp	\
		$(SRC)Brain.cpp	\
		$(SRC)Cell.cpp	\
		$(SRC)Hash.cpp

OBJ	=	$(SRCS:.cpp=.o)

NAME	=	pbrain-RENNES-Tual.Nathan

CXXFLAGS	+=	-Wall -Wextra -I./include -std=c++14

THREAD	=	-lpthread

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) $(THREAD) -o $(NAME)

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
