#include "NeuralNet.hpp"
#include "utils.hpp"
#include <random>

using namespace std;

NeuralNet::NeuralNet(const vector<unsigned int>& net, float (*map)(void*, unsigned int)) : m_map(map)
{
	random_device rd;
	mt19937 gen(rd());
	normal_distribution<> rand;

	m_depth = net.size();
	m_layers = new NeuralNet::Layer[m_depth];
	
	m_layers[0].size = net[0];

	for(size_t i = 1; i < m_depth; i++)
	{
		m_layers[i].size = net[i];
		m_layers[i].biases = new float[net[i]];
		m_layers[i].weights = Matrix(net[i], m_layers[i-1].size);
		for(size_t j = 0; j < net[i]; j++)
		{
			m_layers[i].biases[j] = rand(gen);
			for(size_t k = 0; k < m_layers[i-1].size; k++)
				*(m_layers[i].weights.at(j, k)) = rand(gen);
		}	
	} 
}

NeuralNet::~NeuralNet()
{
	for(size_t i = 1; i < m_depth; i++)
	{
		delete m_layers[i].biases;
	}
	delete m_layers;
}

NeuralTrace NeuralNet::evaluate(void* data)
{
	NeuralTrace trace;
	
	NeuralLayer layer0;
	for(unsigned int i = 0; i < m_layers[0].size; i++)
		layer0.push_back(m_map(data, i));
	
	trace.push_back(layer0);
	
	for(unsigned int i = 1; i < m_depth; i++)
		trace.push_back(evaluate_layer(i, trace[i-1]));
	
	return trace;
}

NeuralLayer NeuralNet::evaluate_layer(unsigned int level, const NeuralLayer& inputs)
{
	#ifdef USE_OPENCL
	#error Not implemented yet.
	#else
	NeuralLayer layer = matrix_vec_mult(m_layers[level].weights, inputs);
	vec_sub(layer, vector<float>(m_layers[level].biases, m_layers[level].biases + m_layers[level].size));
	vec_sigmoid(layer);
	return layer;
	#endif
}
