all:
	g++ -Wall -Wextra -pedantic -o Socket.o -c Socket.cpp
	g++ -Wall -Wextra -pedantic -o GameState.o -c GameState.cpp
	g++ -Wall -Wextra -pedantic -o client client.cpp Socket.o GameState.o
	
clean:
	rm Socket.o
	rm GameState.o
	rm client
