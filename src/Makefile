CXX = g++
CXXFLAGS = -Wall -g
PROG  = johntileengine
OBJS = AnimatedProps.o Bullet.o Camera.o Collision.o Config.o \
	Font.o main.o Mouse.o Player.o Shader.o SoundManager.o \
	Weapon.o World.o ResuplySystem.o Ai.o HealthBar.o \
	Pickup.o
LD = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
VPATH = src

all: $(PROG)

%.o: %.cpp
	$(CXX) -c -o $@ $<

$(PROG): $(OBJS)
	$(CXX) -o $(PROG) $^ $(CXXFLAGS) $(LD)

clean:
	rm -f *.o $(PROG)
