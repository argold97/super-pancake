#include "NeuralNet.hpp"
#include "utils.hpp"
#include <thread>
#include <cmath>

using namespace std;

NeuralNet::Layer::Layer() : biases(nullptr)
{ }

NeuralNet::Layer::~Layer()
{
	delete biases;
}

NeuralNet::NeuralNet(const vector<unsigned int>& topology, float (*map)(void*, unsigned int)) : m_map(map)
{
	normal_distribution<> rand;

	m_depth = topology.size();
	m_topology = new NeuralNet::Layer[m_depth];
	
	m_topology[0].size = topology[0];

	for(size_t i = 1; i < m_depth; i++)
	{
		m_topology[i].size = topology[i];
		m_topology[i].biases = new float[topology[i]];
		m_topology[i].weights = Matrix(topology[i], m_topology[i-1].size);
		for(size_t j = 0; j < topology[i]; j++)
		{
			m_topology[i].biases[j] = rand(gen());
			for(size_t k = 0; k < m_topology[i-1].size; k++)
				*(m_topology[i].weights.at(j, k)) = rand(gen());
		}
	}
}

NeuralNet::~NeuralNet()
{
	delete[] m_topology;
}

NeuralTrace NeuralNet::evaluate(void* data, const Layer* alt)
{
	NeuralTrace trace;
	
	NeuralLayer layer0;
	for(unsigned int i = 0; i < m_topology[0].size; i++)
		layer0.push_back(m_map(data, i));
	
	trace.push_back(layer0);
	
	for(unsigned int i = 1; i < m_depth; i++)
		trace.push_back(evaluate_layer(i, trace[i-1], alt == nullptr ? nullptr : &alt[i]));
	
	return trace;
}

NeuralLayer NeuralNet::evaluate_layer(unsigned int level, const NeuralLayer& inputs, const Layer* alt)
{
	#ifdef USE_OPENCL
	#error Not implemented yet.
	#else
	const Layer* topology = (alt == nullptr) ? m_topology : alt;
	NeuralLayer layer = matrix_vec_mult(topology[level].weights, inputs);
	vec_sub(layer, vector<float>(topology[level].biases, topology[level].biases + topology[level].size));
	vec_sigmoid(layer);
	return layer;
	#endif
}

float NeuralNet::quad_diff(const NeuralLayer& a, const NeuralLayer& b)
{
	float diff = 0.0F;
	for(size_t i = 0; i < a.size(); i++)
	{
		diff += pow(a[i] - b[i], 2);
	}
	return pow(diff, 2);
}

float NeuralNet::train(void** inputs, const NeuralLayer* outputs, unsigned int count, unsigned int iterations, float radius, unsigned int thread_count)
{
	float best_cost;
	Layer* best_topology = nullptr;
	run_iteration(best_cost, best_topology, inputs, outputs, count, radius, true);
	
	float* costs = new float[thread_count];
	Layer** topologies = new Layer*[thread_count];
	thread* threads = new thread[thread_count];
	
	while(iterations > 0)
	{
		unsigned int active = thread_count < iterations ? thread_count : iterations;
		iterations -= active;
		for(unsigned int i = 0; i < active; i++)
			threads[i] = thread(&NeuralNet::run_iteration, this, ref(costs[i]), ref(topologies[i]), inputs, outputs, count, radius, false);
	
		for(unsigned int i = 0; i < active; i++)
		{
			threads[i].join();
			if(costs[i] < best_cost)
			{
				best_cost = costs[i];
				best_topology = topologies[i];
			}else {
				delete[] topologies[i];
			}
		}
	}
	
	if(best_topology != nullptr)
		update_topology(best_topology);
		
	delete[] costs;
	delete[] topologies;
	delete[] threads;
	
	return best_cost;
}

void NeuralNet::run_iteration(float& cost, Layer*& topology, void** inputs, const NeuralLayer* outputs, unsigned int count, float radius, bool base)
{
	cost = 0.0F;
	if(base)
	{
		for(unsigned int i = 0; i < count; i++)
			cost += quad_diff(evaluate(inputs[i])[m_depth - 1], outputs[i]);
	}else {
		normal_distribution<> rand(radius, radius);
		topology = new Layer[m_depth];
		topology[0].size = m_topology[0].size;
		for(unsigned int i = 1; i < m_depth; i++)
		{
			topology[i].size = m_topology[i].size;
			topology[i].biases = new float[m_topology[i].size];
			for(unsigned int j = 0; j < m_topology[i].size; j++)
				topology[i].biases[j] = m_topology[i].biases[j] + binormal(rand(gen()));
			topology[i].weights = m_topology[i].weights;
			for(unsigned int j = 0; j < topology[i].weights.rows(); j++)
				for(unsigned int k = 0; k < topology[i].weights.cols(); k++)
					*topology[i].weights.at(j, k) += binormal(rand(gen()));
		}
		for(unsigned int i = 0; i < count; i++)
			cost += quad_diff(evaluate(inputs[i], topology)[m_depth - 1], outputs[i]);
	}
	cost /= count;
}

void NeuralNet::update_topology(Layer* topology)
{
	delete[] m_topology;
	m_topology = topology;
}
