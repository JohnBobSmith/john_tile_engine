CXX = g++
CXXFLAGS = -Wall -g
PROG  = johntileengine
ODIR  = obj
SRC = $(wildcard *.cpp)
OBJS = $(addprefix $(ODIR)/,$(SRC:.cpp=.o))
LD = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: $(PROG)

$(ODIR)/%.o: %.cpp
	mkdir -p $(ODIR)
	$(CXX) -c -o $@ $^

$(PROG): $(OBJS)
	$(CXX) -o $(PROG) $^ $(CXXFLAGS) $(LD)

clean:
	rm -f $(ODIR)/*.o johntileengine
	
.PHONY: clean
