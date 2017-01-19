CC=g++
CC_FLAGS=-std=gnu++14

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: fsquery

fsquery: $(OBJECTS)
	$(CC) $(CC_FLAGS) $(OBJECTS) -o fsquery

%.o: %.cpp
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) fsquery
