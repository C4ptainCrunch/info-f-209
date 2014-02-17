all:
	g++ -Wall -Wextra -pedantic -o Socket.o -c Socket.cpp
	g++ -Wall -Wextra -pedantic -o GameState.o -c GameState.cpp
	g++ -Wall -Wextra -pedantic -o utilitary.o -c utilitary.cpp
	g++ -Wall -Wextra -pedantic -o client client.cpp Socket.o GameState.o utilitary.o
	
clean:
	rm Socket.o
	rm GameState.o
	rm utilitary.o
	rm client
