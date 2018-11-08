SRC_DIR := ./src
INC_DIR := ./include
OBJ_DIR := ./obj
CC := g++
CFLAGS := -std=c++17 -g
LDFLAGS := -lgmpxx -lgmp
TARGET := postgres_ext
INC := -I include/

SRCS := $(wildcard $(SRC_DIR)/*.cpp postgres_ext.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

ch:
	g++ -g -o ./obj/ConvexHull/Chans.o ./src/ConvexHull/Chans.cpp -c
	g++ -g -o ./obj/ConvexHull/DivideAndConquer.o ./src/ConvexHull/DivideAndConquer.cpp -c
	g++ -g -o convexHullAnalysis obj/ConvexHull/DivideAndConquer.o obj/ConvexHull/Chans.o ConvexHullAnalysis.cpp

clean:
	rm -rf $(TARGET) $(OBJ_DIR)/*.o
	
.PHONY: all clean
