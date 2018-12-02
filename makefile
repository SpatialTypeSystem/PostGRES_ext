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
	g++ -g -o ./obj/ConvexHull/Utils.o ./src/ConvexHull/Utils.cpp -c
	g++ -g -o ./obj/ConvexHull/Chans.o ./src/ConvexHull/Chans.cpp -c
	g++ -g -o ./obj/ConvexHull/DivideAndConquer.o ./src/ConvexHull/DivideAndConquer.cpp -c
	g++ -g -o ./obj/ConvexHull/Graham.o ./src/ConvexHull/Graham.cpp -c
	g++ -g -o convexHullAnalysis obj/ConvexHull/Utils.o obj/Number.o obj/RGPPoint2D.o obj/ConvexHull/DivideAndConquer.o obj/ConvexHull/Chans.o obj/ConvexHull/Graham.o ConvexHullAnalysis.cpp -lgmpxx -lgmp

clean:
	rm -rf $(TARGET) $(OBJ_DIR)/*.o
	
.PHONY: all clean
