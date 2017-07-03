#ifndef NEURALNET_H
#define NEURALNET_H

#include "Matrix.hpp"
#include <vector>
#include <random>

#define NeuralLayer std::vector<float>
#define NeuralTrace std::vector<NeuralLayer>

class NeuralNet
{
	private:
	class Layer
	{
		public:
		Layer();
		~Layer();
		unsigned int size;
		float* biases;
		Matrix weights;
	};

	public:
	NeuralNet(const std::vector<unsigned int>& topology, float (*map)(void*, unsigned int));
	~NeuralNet();
	NeuralTrace evaluate(void* data, const Layer* alt = nullptr);
	float train(void** inputs, const NeuralLayer* outputs, unsigned int count, unsigned int iterations, float radius, unsigned int thread_count = 1);

	private:	
	NeuralLayer evaluate_layer(unsigned int level, const NeuralLayer& inputs, const Layer* alt = nullptr);
	float quad_diff(const NeuralLayer& a, const NeuralLayer& b);
	void run_iteration(float& cost, Layer*& topology, void** inputs, const NeuralLayer* outputs, unsigned int count, float radius, bool base = false);
	void update_topology(Layer* topology);
	
	unsigned int m_depth;
	Layer* m_topology;
	float (*m_map)(void*, unsigned int);
};

#endif
