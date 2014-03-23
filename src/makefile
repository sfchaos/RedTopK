CXX = g++
TARGET = redtopk
CXXFLAGS = -Wall -std=c++11
INCLUDES = -I /usr/local/include -I ../lib
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -f $(TARGET) $(OBJECTS)
