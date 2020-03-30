OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN1=Disk
BIN2=Ring
BIN3=Square
SRCS1=Disk.cpp GL_Framework/gl_framework.cpp Shader/shader_util.cpp
SRCS2=Ring.cpp GL_Framework/gl_framework.cpp Shader/shader_util.cpp
SRCS3=Square.cpp GL_Framework/gl_framework.cpp Shader/shader_util.cpp
INCLUDES=GL_Framework/gl_framework.hpp Shader/shader_util.hpp

all: $(BIN1) $(BIN2) $(BIN3)

$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)

$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)

$(BIN3): $(SRCS3) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS3) -o $(BIN3) $(LDFLAGS) $(LIBS)
clean:
	rm -f *~ *.o $(BIN1) $(BIN2) $(BIN3)
