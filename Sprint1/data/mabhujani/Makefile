all: build-obj build-bin

build-bin:
		g++ -o server smain.cpp server.o user.o
		g++ -o client cmain.cpp client.o
build-obj:
		g++ -c server.cpp
		g++ -c user.cpp
		g++ -c client.cpp

