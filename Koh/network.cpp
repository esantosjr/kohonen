#include "network.h"
#include <math.h>
#include <algorithm>
#include <opencv2/opencv.hpp>

using namespace std;

void Network::create(int width, int height, int sizeOfInputVector, int NumIterations) {

  numIterations = NumIterations; // t
  sizeInputVector = sizeOfInputVector;
  size = width * height;

  // cria todos os nós
  for(int i = 0; i < width; i++) {
      for(int j = 0; j < height; j++)
          SOM.push_back(Node(sizeInputVector, i, j));
  }

  mapRadius = max(width, height) / 2; // sigma zero
  time = numIterations / log(mapRadius); // tau
}

bool Network::epoch(vector<vector<double> > &data) {

  // garante que o tamanho do vetor de entrada seja igual ao tamanho do vetor de pesos.
  if(data[0].size() != sizeInputVector)
      return false;

  // retorna se o treinamento já foi finalizado.
  if(trainDone)
      return true;

  if(--numIterations > 0) {
        // seleciona um vetor randômico de entrada.
        int vec = rand() % (data.size());

        winningNode = findNearestNode(data[vec]);

        // calcula o tamanho do raio da vizinhança. Este valor tenderá a zero.
        neighbourhoodRadius = mapRadius * exp(-(double)iterationCount/time); // sigma(t)

        // ajusta o peso e a vizinhança do neurônio vencedor.
        for(uint n = 0; n < SOM.size(); ++n) {
              // calcula a distância do nó atual em relação ao nó vencedor
              double DistToNode = pow(winningNode->get_position_x() - SOM[n].get_position_x(), 2) + pow(winningNode->get_position_y() - SOM[n].get_position_y(), 2);

              double Width = neighbourhoodRadius * neighbourhoodRadius;

              // se está dentro da vizinhança, ajusta o peso
              if(DistToNode < Width) {
                    // calcula quanto o peso do nó será ajustado
                    influence = exp(-(DistToNode) / (2 * Width));
                    SOM[n].AdjustWeights(data[vec], learningRate, influence);
              }
        } // próximo nó

        // reduz learning rate L(t) (tende a zero).
        learningRate = startLearningRate * exp(-(double)iterationCount/numIterations);
        ++iterationCount;
  } else {
      trainDone = true;
  }
  return true;
}

bool Network::finishedTraining() {
    return trainDone;
}

Node* Network::findNearestNode(vector<double> &vector) {
  Node* winner = NULL;
  double LowestDistance = 999999;

  for(uint i = 0; i < SOM.size(); i++) {
      double dist = SOM[i].CalculateDistance(vector);
      if (dist < LowestDistance) {
          LowestDistance = dist;
          winner = &SOM[i];
      }
  }
  return winner;
}

vector<Node> Network::get_SOM() {
    return SOM;
}

int Network::getSize() {
    return size;
}

void Network::set_startLR(double startLearningRt) {
    startLearningRate = startLearningRt;
}

void Network::set_iterations(int niterations) {
    numIterations = niterations;
}

int Network::get_iterations() {
    return iterationCount;
}
