#ifndef NETWORK_H
#define NETWORK_H

#include "node.h"
#include <vector>

class Network {

private:
     vector<Node> SOM;
     Node * winningNode;
     double mapRadius, time, neighbourhoodRadius, influence, learningRate;
     int numIterations, iterationCount, size;
     uint sizeInputVector;
     bool trainDone;

     double startLearningRate;

public:
    Network(double startLR) {
        startLearningRate = startLR;
        winningNode = NULL;
        iterationCount = 1;
        numIterations = 0;
        time = 0;
        mapRadius = 0;
        neighbourhoodRadius = 0;
        influence = 0;
        learningRate = startLearningRate;
        trainDone = false;
    }

    void operator = (const Network& original) {
        this->startLearningRate = original.startLearningRate;
        this->iterationCount = original.iterationCount;
        this->numIterations = original.numIterations;
        this->time = original.time;
        this->mapRadius = original.mapRadius;
        this->neighbourhoodRadius = original.neighbourhoodRadius;
        this->influence = original.influence;
        this->learningRate = original.learningRate;
        this->trainDone = original.trainDone;
        this->sizeInputVector = original.sizeInputVector;
        this->size = original.size;
        this->SOM = original.SOM;
        this->winningNode = NULL;
    }

    Node* findNearestNode(vector<double> &vector);
    void create(int width, int height, int sizeInputVector, int NumIterations);
    bool epoch(vector<vector<double> > &data);
    bool finishedTraining();
    vector<Node> get_SOM();
    int getSize();
    void set_startLR(double startLearningRt);
    void set_iterations(int niterations);
    int get_iterations();
};

#endif // NETWORK_H
