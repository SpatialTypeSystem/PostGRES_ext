SRC_DIR := ./src
TST_DIR := ./test
INC_DIR := ./include
OBJ_DIR := ./obj
CC := g++
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
test: $(TST_DIR)/NumberTest
$(TST_DIR)/NumberTest: $(OBJ_DIR)/Number.o $(TST_DIR)/NumberTest.cpp
	$(CC) $(CFLAGS) $(LIB) -o $@ $^ $(INC) $(LDFLAGS_TST)
	./$(TST_DIR)/NumberTest
clean:
	rm -rf $(TARGET) $(OBJ_DIR)/*.o
	
.PHONY: all clean