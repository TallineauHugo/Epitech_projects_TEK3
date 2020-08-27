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

GUI	=	$(OTTER)GUI/

SPRITE	=	$(OTTER)SpriteManager/

MUSIC	=	$(OTTER)Music/

SRCS	=	$(SRC)main.cpp \
		$(SRC)NetworkManager.cpp \
		$(SRC)Client.cpp \
		$(SRC)Mutex.cpp \
		$(SRC)ScopedLock.cpp \
		$(SRC)SafeQueue.cpp \
		$(SRC)Player.cpp \
		$(SRC)ZigZagEnnemy.cpp \
		$(SRC)Bullet.cpp \
		$(SRC)SpaceShip.cpp \
		$(SRC)EnnemySpaceShip.cpp \
		$(SRC)Bomb.cpp \
		$(SRC)Energy.cpp \
		$(SRC)Id.cpp \
		$(SRC)Explosion.cpp \
		$(OTTER)Object.cpp \
		$(OTTER)OtterEngine.cpp \
		$(OTTER)View.cpp \
		$(OTTER)WindowManager.cpp \
		$(OTTER)InputManager.cpp \
		$(OTTER)Hitbox.cpp \
		$(OTTER)TimeManager.cpp \
		$(SPRITE)SpritesManager.cpp \
		$(SPRITE)FixedSprite.cpp \
		$(SPRITE)AnimatedSprite.cpp \
		$(SPRITE)MultiAnimatedSprite.cpp \
		$(SPRITE)TextSprite.cpp \
		$(GUI)Button.cpp \
		$(GUI)Menu.cpp \
		$(GUI)MenuElement.cpp \
		$(GUI)Slider.cpp \
		$(GUI)SpriteSlider.cpp \
		$(MUSIC)MusicManager.cpp \
		$(MUSIC)SoundManager.cpp

OBJ	=	$(SRCS:.cpp=.o)

NAME	=	../client

SFML	=	-lsfml-network -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -lpthread

CXXFLAGS	+=	-Wall -Wextra -I./include -I../OtterEngine/include -I../OtterEngine/include/SpriteManager -I../OtterEngine/include/Music -I../OtterEngine/include/GUI -std=c++14

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(SFML)

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
