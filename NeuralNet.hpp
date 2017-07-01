#ifndef NEURALNET_H
#define NEURALNET_H

#include "Matrix.hpp"
#include <vector>

#define NeuralLayer std::vector<float>
#define NeuralTrace std::vector<NeuralLayer>

class NeuralNet
{
	public:
	NeuralNet(const std::vector<unsigned int>& net, float (*map)(void*, unsigned int));
	~NeuralNet();
	NeuralTrace evaluate(void* data);

	private:
	struct Layer
	{
		unsigned int size;
		float* biases;
		Matrix weights;
	};
	
	NeuralLayer evaluate_layer(unsigned int level, const NeuralLayer& inputs);
	
	unsigned int m_depth;
	Layer* m_layers;
	float (*m_map)(void*, unsigned int);
};

#endif
