
SRC		=	main.cpp \
			Game.cpp \
			Intro.cpp \
			Menu.cpp \
			Fault.cpp \
			Graphics.cpp \
			FBORenderer.cpp \
			FBOShader.cpp \
			BasicShader.cpp \
			PanShader.cpp \
			Ia.cpp \
			GameEngine.cpp \
			Map.cpp \
			PThread.cpp \
			PMutex.cpp \
			PCondVar.cpp \
			ScopeLock.cpp \
			Player.cpp \
			Wall.cpp \
			Box.cpp \
			Bomb.cpp \
			AObject.cpp \
			Cube.cpp \
			ACamera.cpp \
			FreeCam.cpp \
			BasicCam.cpp \
			ArmagetroCam.cpp \
			FpsCam.cpp \
			TrackCam.cpp \
			OrthoCam.cpp \
			FontText.cpp \
			EntitiesFactory.cpp \
			AssetsManager.cpp \
			Pan.cpp \
			Ground.cpp \
			Placement.cpp \
			APlayer.cpp \
			Model.cpp \
			PivotingCam.cpp \
			Light.cpp \
			Cube6Face.cpp \
			SkyBox.cpp

CC		=	g++

FILETYPE	=	.cpp

RM		=	rm -f

NAME		=	bomberman

OBJDIR		=	obj/
SRCDIR		=	src/
INCDIR		=	include/

CFLAGS		+=	-I$(INCDIR) -Ilib/include/
CFLAGS		+=	-Wall -Wextra -Winit-self
CFLAGS		+=	-Wunused-function -pipe

LDFLAGS		+=	-Wl,-O1
LDFLAGS		+=	-lpthread
LDFLAGS		+=	-Wl,-rpath="`pwd`/lib"
LDFLAGS		+=	-Llib -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -llua5.2

OBJ		=	$(patsubst %${FILETYPE}, ${OBJDIR}%.o, $(SRC))
DEPS		=	$(patsubst %${FILETYPE}, ${OBJDIR}%.d, $(SRC))

PRINTFLAGS	=	0

dummy		:=	$(shell test -d $(OBJDIR) || mkdir -p $(OBJDIR))
dummy		:=	$(shell test -d $(SRCDIR) || mkdir -p $(SRCDIR))
dummy		:=	$(shell test -d $(INCDIR) || mkdir -p $(INCDIR))

$(OBJDIR)%.o:		$(patsubst %${FILETYPE}, ${SRCDIR}%${FILETYPE}, %${FILETYPE})
			@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
ifneq ("$(shell tty)", "not a tty")
			@if [ $(PRINTFLAGS) = "0" ]; then \
			echo -e "Compile flags { $(CFLAGS) }" | sed 's/^-e //' \
			| sed 's/[-a-zA-Z]\+/\x1B[31m&\x1B[0m/g' \
			| sed 's/[A-Z]\+/\x1B[32m&\x1B[0m/g' \
			| sed 's/[{}]/\x1B[34m&\x1B[0m/g'; fi
			$(eval PRINTFLAGS = 1)
			@echo -e "Compiling $< $(patsubst %.o, %.d, $@)" | sed 's/^-e //' \
			| sed 's/[-a-zA-Z]\+/\x1B[31m&\x1B[0m/g' \
			| sed 's/[A-Z]\+/\x1B[32m&\x1B[0m/g' | sed 's/d/\x1B[35m&\x1B[0m/'
			@$(CC) $(CFLAGS) -c $< -o $@
			@$(CC) $(CFLAGS) -MM -MF $(patsubst %.o, %.d, $@) -MT $@ -MT $(patsubst %.o, %.d, $@) -c $<
else
			$(CC) $(CFLAGS) -c $< -o $@
			$(CC) $(CFLAGS) -MM -MF $(patsubst %.o, %.d, $@) -MT $@ -MT $(patsubst %.o, %.d, $@) -c $<
endif

$(NAME):	$(OBJ)
ifneq ("$(shell tty)", "not a tty")
		@echo -e "Linking $@ { $(LDFLAGS) }" | sed 's/^-e //' \
		| sed 's/[-a-zA-Z]\+/\x1B[34m&\x1B[0m/g'
		@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
else
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
endif

-include $(DEPS)

all:	$(NAME)

clean:
ifneq ("$(shell tty)", "not a tty")
	@echo -e "Removing object !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[35m&\x1B[0m/g'
	@$(RM) $(OBJ) $(DEPS)
else
	$(RM) $(OBJ) $(DEPS)
endif

fclean:	clean
ifneq ("$(shell tty)", "not a tty")
	@echo -e "Removing ${NAME} !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[36m&\x1B[0m/g'
	@$(RM) $(NAME)
else
	$(RM) $(NAME)
endif

re:	fclean all

help:
	@echo -e "\033[37mTarget available: all, ${NAME}, clean, fclean, help\033[00m" | sed 's/^-e //'

.PHONY:	all clean fclean re help
