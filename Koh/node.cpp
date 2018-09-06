#include "node.h"
#include <math.h>

double Node::CalculateDistance(vector<double> &inputVector) {
  double distance = 0;

  for(uint i = 0; i < weights.size(); i++) {
            distance += (inputVector[i] - weights[i]) * (inputVector[i] - weights[i]);
  }
  return distance;
}

void Node::AdjustWeights(vector<double> &vector, double learningRate, double influence) {
    for(uint i = 0; i < vector.size(); i++)
            weights[i] += learningRate * influence * (vector[i] - weights[i]);
}

double Node::get_position_x() {
    return x_position;
}

double Node::get_position_y() {
    return y_position;
}

vector<double> Node::get_weights() {
    return weights;
}
