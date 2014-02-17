all:
	g++ -Wall -Wextra -pedantic -o ../lib/socket/Socket.o -c ../lib/socket/Socket.cpp
	g++ -Wall -Wextra -pedantic -o GameState.o -c GameState.cpp
	g++ -Wall -Wextra -pedantic -o utilitary.o -c utilitary.cpp
	g++ -Wall -Wextra -pedantic -o client client.cpp ../lib/socket/Socket.o GameState.o utilitary.o

clean:
	rm ../lib/socket/Socket.o
	rm GameState.o
	rm utilitary.o
	rm client
