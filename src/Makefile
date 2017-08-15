CC = g++
CFLAGS = -Wall -g
DEPS = AnimatedProps.h Bullet.h Camera.h Collision.h Config.h \
	Font.h Mouse.h Player.h Shader.h SoundManager.h Weapon.h World.h
OBJ = AnimatedProps.o Bullet.o Camera.o Collision.o Config.o \
	Font.o main.o Mouse.o Player.o Shader.o SoundManager.o Weapon.o\
	World.o
LD = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

johntileengine: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LD)

clean:
	rm -f *.o johntileengine
