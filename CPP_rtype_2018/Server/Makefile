##
## EPITECH PROJECT, 2018
## 301dannon
## File description:
## makefile
##

CC	=	g++

RM	=	rm -f

SRC	=	src/

OTTER	=	../OtterEngine/src/

SRCS	=	$(SRC)main.cpp \
		$(SRC)Server.cpp \
		$(SRC)NetworkManager.cpp \
		$(SRC)Logger.cpp \
		$(SRC)Mutex.cpp \
		$(SRC)ScopedLock.cpp \
		$(SRC)SafeQueue.cpp \
		$(SRC)Parser.cpp \
		$(SRC)Player.cpp \
		$(SRC)Lobby.cpp \
		$(SRC)ClientServer.cpp \
		$(SRC)Game.cpp \
		$(SRC)Energy.cpp \
		$(SRC)EnnemySpaceShip.cpp \
		$(SRC)SpaceShip.cpp \
		$(SRC)ZigZagEnnemy.cpp \
		$(SRC)Bullet.cpp \
		$(SRC)Bomb.cpp \
		$(SRC)Explosion.cpp \
		$(SRC)Id.cpp \
		$(OTTER)GUI/Button.cpp \
		$(OTTER)GUI/MenuElement.cpp \
		$(OTTER)GUI/Slider.cpp \
		$(OTTER)GUI/SpriteSlider.cpp \
		$(OTTER)Hitbox.cpp \
		$(OTTER)InputManager.cpp \
		$(OTTER)Music/MusicManager.cpp \
		$(OTTER)Music/SoundManager.cpp \
		$(OTTER)Object.cpp \
		$(OTTER)OtterEngine.cpp \
		$(OTTER)SpriteManager/AnimatedSprite.cpp \
		$(OTTER)SpriteManager/MultiAnimatedSprite.cpp \
		$(OTTER)SpriteManager/FixedSprite.cpp \
		$(OTTER)SpriteManager/SpritesManager.cpp \
		$(OTTER)SpriteManager/TextSprite.cpp \
		$(OTTER)TimeManager.cpp \
		$(OTTER)View.cpp \
		$(OTTER)WindowManager.cpp

OBJ	=	$(SRCS:.cpp=.o)

NAME	=	../server

BOOST	=	-lboost_system -lpthread -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CXXFLAGS	+=	-Wall -Wextra -I./include -I../OtterEngine/include -I../OtterEngine/include/GUI -I../OtterEngine/include/Music -I../OtterEngine/include/SpriteManager -std=c++11

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(BOOST)

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
