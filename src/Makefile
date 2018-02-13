CXX = g++
CXXFLAGS = -g -Wall
PROG  = johntileengine
ODIR  = obj
#SRC = $(wildcard *.cpp $(wildcard nope/*.cpp))
SRC = $(wildcard *.cpp)
OBJS = $(addprefix $(ODIR)/,$(SRC:.cpp=.o))
LD = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: $(PROG)

$(ODIR)/%.o: %.cpp
	mkdir -p $(ODIR)
	$(CXX) -c -o $@ $^ $(CXXFLAGS)

$(PROG): $(OBJS)
	$(CXX) -o $(PROG) $^ $(LD)

clean:
	rm -f $(ODIR)/*.o johntileengine 
	
.PHONY: clean
