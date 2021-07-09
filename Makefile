all: mandelbrot

mandelbrot : main.o Mesh.o Shader.o Window.o
	g++ -o mandelbrot main.o Mesh.o Shader.o Window.o -framework OpenGL -lglfw -lGLEW

main.o: main.cpp
	g++ -c main.cpp

Mesh.o: Mesh.cpp
	g++ -c Mesh.cpp

Shader.o: Shader.cpp
	g++ -c Shader.cpp

Window.o: Window.cpp
	g++ -c Window.cpp
	
clean:
	rm -f *.o

