CC = g++
EXECNAME = super-pancake
SRCFILES = main.cpp Matrix.cpp NeuralNet.cpp utils.cpp

build: $(OBJFILES)
	$(CC) -g -Wall -o $(EXECNAME) $(SRCFILES)

opencl: $(OBJFILES)
	$(CC) -g -Wall -D USE_OPENCL -o $(EXECNAME) $(SRCFILES)

clean:
	rm -rf $(EXECNAME) *.o
