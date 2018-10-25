PROGRAM = mainProgram
CC		= gcc
CFLAGS	= -Wall -Wextra
LDLIBS  = -lGL -lGLU -lglut -lm

$(PROGRAM): mainProgram.o mainScene.o mainHUD.o mainTexture.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

mainProgram.o: mainProgram.c
	$(CC) -c $<

mainScene.o: mainScene.c mainScene.h
	$(CC) -c $<

mainHUD.o: mainHUD.c mainHUD.h
	$(CC) -c $<

mainTexture.o: mainTexture.c mainTexture.h
	$(CC) -c $<

mainMenu: mainMenu.o mainTexture.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

mainMenu.o: mainMenu.c
	$(CC) -c $<

.PHONY: clean

clean:
	rm -rf $(PROGRAM) mainMenu *.o