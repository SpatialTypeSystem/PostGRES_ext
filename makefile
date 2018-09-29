CFLAGS = -std=c++17 -O
CC = g++
SRC = *.cpp
OBJ = $(SRC:.cpp = .o)
NumTest: $(OBJ)
	$(CC) $(CFLAGS) -o Postgres_ext $(OBJ) 
clean:
	rm -f core *.o
