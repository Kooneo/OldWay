CXX = g++
CXXSTD = -std=c++17

CXXFLAGS = $(CXXSTD) -Wall -Wextra -g

TARGET = OldWay
BACKUPFILE=./backup/hosts.backup
SRCS = Main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: all
	sudo ./$(TARGET)
	rm -f $(OBJS) $(TARGET)

backup:
	sudo mv -f $(BACKUPFILE) /etc/hosts

.PHONY: backup all clean run