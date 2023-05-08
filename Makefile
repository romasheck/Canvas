all:
	g++ src/GEO/*.cpp src/*.cpp -o build/prog -lsfml-graphics -lsfml-window -Wextra -lsfml-system