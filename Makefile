PROGRAM = WesternFront
CC		= gcc
CFLAGS	= -Wall -Wextra
LDLIBS  = -lGL -lGLU -lglut -lm

$(PROGRAM): main_program.o scene.o hud.o texture.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

main_program.o: source/main_program.c
	$(CC) -c $<

scene.o: source/scene.c headers/scene.h
	$(CC) -c $<

hud.o: source/hud.c headers/hud.h
	$(CC) -c $<

texture.o: source/texture.c headers/texture.h
	$(CC) -c $<

main_menu: main_menu.o texture.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

main_menu.o: source/main_menu.c
	$(CC) -c $<

.PHONY: clean

clean:
	rm -rf $(PROGRAM) main_menu *.o