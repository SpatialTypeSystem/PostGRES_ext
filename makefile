SRC_DIR := ./src
TST_DIR := ./test
INC_DIR := ./include
OBJ_DIR := ./obj
CC := g++-7
CFLAGS := -std=c++17 -g
LDFLAGS := -lgmpxx -lgmp
LDFLAGS_TST := -lgmpxx -lgmp -lboost_unit_test_framework
TARGET := postgres_ext
INC := -I include/ -I$(HOME)/.local/include
LIB := -L$(HOME)/.local/lib

SRCS := $(wildcard $(SRC_DIR)/*.cpp postgres_ext.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LIB) -o $@ $^ $(LDFLAGS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

chdata:
	g++-7 -g -o createPointsData CreatePointsData.cpp
	
ch:
	g++-7 -g -o ./obj/ConvexHull/Utils.o ./src/ConvexHull/Utils.cpp -c
	g++-7 -g -o ./obj/ConvexHull/Chans.o ./src/ConvexHull/Chans.cpp -c
	g++-7 -g -o ./obj/ConvexHull/DivideAndConquer.o ./src/ConvexHull/DivideAndConquer.cpp -c
	g++-7 -g -o ./obj/ConvexHull/MonotoneChain.o ./src/ConvexHull/MonotoneChain.cpp -c
	g++-7 -g -o ./obj/ConvexHull/GrahamScan.o ./src/ConvexHull/GrahamScan.cpp -c
	g++-7 -g -o ./obj/ConvexHull/JarvisMarch.o ./src/ConvexHull/JarvisMarch.cpp -c
	g++-7 -g -o ./obj/ConvexHull/QuickHull.o ./src/ConvexHull/QuickHull.cpp -c
	g++-7 -g -o convexHullAnalysis obj/ConvexHull/Utils.o obj/Number.o obj/RGPPoint2D.o obj/ConvexHull/DivideAndConquer.o obj/ConvexHull/Chans.o obj/ConvexHull/GrahamScan.o obj/ConvexHull/MonotoneChain.o obj/ConvexHull/JarvisMarch.o obj/ConvexHull/QuickHull.o ConvexHullAnalysis.cpp -lgmpxx -lgmp

test: $(TST_DIR)/NumberTest
$(TST_DIR)/NumberTest: $(OBJ_DIR)/Number.o $(TST_DIR)/NumberTest.cpp
	$(CC) $(CFLAGS) $(LIB) -o $@ $^ $(INC) $(LDFLAGS_TST)
	./$(TST_DIR)/NumberTest

clean:
	rm -rf $(TARGET) $(OBJ_DIR)/*.o
	
.PHONY: all clean
