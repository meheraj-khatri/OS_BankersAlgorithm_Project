CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = bankers
SRCDIR = src
INCDIR = include
SOURCES = $(SRCDIR)/bankers.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run