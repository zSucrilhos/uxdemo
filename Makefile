uxtest: main.cc util.cc shaders.cc shapes.cc vertex.cc texture.cc
	g++ -lfreetype -lSOIL -lglut -lGLU -lGL -Iinclude -I/usr/include/freetype2 --std=c++11 main.cc util.cc shaders.cc shapes.cc vertex.cc texture.cc -o uxtest

clean: 
	rm uxtest
