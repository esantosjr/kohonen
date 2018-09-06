#ifndef NODE_H
#define NODE_H
#include <vector>
#include <cstdlib>
#include <opencv2/opencv.hpp>

using namespace std;

class Node {

private:
    vector<double> weights; // cada nó da rede possui um vetor de pesos.
    double x_position, y_position; // posição do nó na rede.

public:
    Node(int sizeInputVector, int position_x, int position_y) {
        for(int j = 0; j < sizeInputVector; j++) {
            weights.push_back(rand() / (RAND_MAX+1.0));
            x_position = position_x;
            y_position = position_y;
        }
    }

    void operator = (const Node &original) {
        this->weights = original.weights;
        this->x_position = original.x_position;
        this->y_position = original.y_position;
    }

    double CalculateDistance(vector<double> &inputVector);
    void AdjustWeights(vector<double> &vector, double learningRate, double influence);
    double get_position_x();
    double get_position_y();
    vector<double> get_weights();
};

#endif // NODE_H
