#ifndef KOHONEN_H
#define KOHONEN_H

#include "node.h"
#include "network.h"
#include <string.h>

class Kohonen {

private:
    Network* pSOMoriginal;
    Network* pSOM;

public:
    Kohonen(int width, int height, int sizeInputVector, int NumIterations, double startLR) {
        pSOMoriginal = new Network(startLR);
        pSOMoriginal->create(width, height, sizeInputVector, NumIterations);
        pSOM = new Network(startLR);
        *pSOM = *pSOMoriginal;
    }

    ~Kohonen() {
        delete pSOMoriginal;
        delete pSOM;
    }

    vector<vector<double> > training_set;

    bool train();
    bool finished();
    Network get_pSOMoriginal();
    Network get_pSOM();
    void set_pSOM(Network net);
    void set_startLearningRate(double startLearningRt);
    void set_NumIterations(int niterations);
    int get_itCount();
};

#endif // KOHONEN_H
