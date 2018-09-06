#include "kohonen.h"

bool Kohonen::train() {
    if(!pSOM->finishedTraining()) {
        if(!pSOM->epoch(training_set))
          return false;
    }
    return true;
}

bool Kohonen::finished() {
    return pSOM->finishedTraining();
}

Network Kohonen::get_pSOMoriginal() {
    return *pSOMoriginal;
}

Network Kohonen::get_pSOM() {
    return *pSOM;
}

void Kohonen::set_pSOM(Network net) {
    *pSOM = net;
}

void Kohonen::set_startLearningRate(double startLearningRt) {
    pSOMoriginal->set_startLR(startLearningRt);
}

void Kohonen::set_NumIterations(int niterations) {
    pSOMoriginal->set_iterations(niterations);
}

int Kohonen::get_itCount() {
    return pSOM->get_iterations();
}
