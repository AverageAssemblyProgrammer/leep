CFLAGS=-Wall -Wextra -std=c++17

example: example.cpp
	g++ example.cpp -o example $(CFLAGS)

example.cpp:
	
