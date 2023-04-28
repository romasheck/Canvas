all:
	g++ src/*.cpp -o build/prog -lsfml-graphics -lsfml-window -Wextra -Wconversion -lsfml-system