all:
	g++ src/*.cpp src/GUI/*.cpp -o build/prog -lsfml-graphics -lsfml-window -lsfml-system