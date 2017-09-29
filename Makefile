CXX = g++
CXXFLAGS = -Wall -g
OBJ = AnimatedProps.o Bullet.o Camera.o Collision.o Config.o \
	Font.o main.o Mouse.o Player.o Shader.o SoundManager.o \
	Weapon.o World.o ResuplySystem.o Ai.o
LD = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
ODIR = obj
	
%.o: %.c
	$(CXX) -c $< -o $(ODIR)/$@

johntileengine: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LD)

.PHONY: clean

clean:
	rm -f *.o johntileengine
