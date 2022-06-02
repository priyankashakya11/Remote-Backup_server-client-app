CC=g++
CF=-g -Wall
BIN=../bin
SRC=../src
INC=../include
OBJ=../obj
IF= -I $(INC)

all: build-client build-server

build-client: $(OBJ)/client.o $(SRC)/cmain.cpp
		$(CC) $(IF) $(CF) $(OBJ)/client.o $(SRC)/cmain.cpp -o $(BIN)/client

build-server: $(OBJ)/server.o $(SRC)/smain.cpp $(OBJ)/user.o
		$(CC) $(IF) $(CF) $(OBJ)/server.o $(OBJ)/user.o $(SRC)/smain.cpp -o $(BIN)/server -lstdc++fs

$(OBJ)/client.o: $(SRC)/client.cpp
		$(CC) -c $(SRC)/client.cpp -o $(OBJ)/client.o

$(OBJ)/server.o: $(SRC)/server.cpp
		$(CC) -c $(SRC)/server.cpp -o $(OBJ)/server.o

$(OBJ)/user.o: $(SRC)/user.cpp
		$(CC) -c $(SRC)/user.cpp -o $(OBJ)/user.o

clean:
		rm $(BIN)/client $(BIN)/server $(OBJ)/client.o $(OBJ)/server.o $(OBJ)/user.o
