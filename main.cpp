#include "NeuralNet.hpp"
#include <iostream>
#include <vector>

using namespace std;

float map(void* data, unsigned int index)
{
	return ((float*)data)[index];
}

int main(int argc, char** argv)
{
	vector<unsigned int> topology = {9, 20, 5};
	
	NeuralNet network(topology, map);

	float sample[10] = {-0.4F, -0.3F, -0.2F, -0.1F, 0.0F, 0.1F, 0.2F, 0.3F, 0.4F};

	NeuralTrace trace = network.evaluate((void*)&sample[0]);

	for(size_t i = 0; i < 3; i++)
	{
		for(size_t j = 0; j < trace[i].size(); j++)
			cout << trace[i][j] << " ";
		cout << endl;
	}
	
	return 0;
}
