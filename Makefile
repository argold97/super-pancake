CC = g++
CPPFLAGS= -g -Wall
EXECNAME = super-pancake
EXECNAME2 = super-pancake-opencl
BASEOBJS = Matrix.o NeuralNet.o utils.o
BASEOBJS_OPENCL = Matrix.o NeuralNet_opencl.o utils.o
MAINOBJS = main.o

build: $(EXECNAME)

build-opencl: $(EXECNAME2)

$(EXECNAME): $(MAINOBJS) $(BASEOBJS)
	$(CC) -o $(EXECNAME) $(MAINOBJS) $(BASEOBJS)

$(EXECNAME2): $(MAINOBJS) $(BASEOBJS_OPENCL)
	$(CC) -o $(EXECNAME2) $(MAINOBJS) $(BASEOBJS_OPENCL)

NeuralNet_opencl.o:
	$(CC) $(CPPFLAGS) -D USE_OPENCL NeuralNet.cpp

clean:
	rm -rf $(EXECNAME) $(EXECNAME2) *.o
