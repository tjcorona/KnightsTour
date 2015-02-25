#ifndef KTNEURALNETWORK_HH
#define KTNEURALNETWORK_HH

#include "KTAdjacencyList.hh"
#include "KTKnightGraph.hh"

namespace KT
{
  class NeuralNetwork
  {
  public:
    NeuralNetwork() : fIteration(0), fHistoryLength(10) {}
    virtual ~NeuralNetwork() {}

    Solution FindTour(const KnightGraph& graph,bool requireFullTour=false);

  private:
    bool fStable;
    unsigned fIteration;
    std::vector<int> fState;
    std::vector<bool> fOutput;
    unsigned fHistoryLength;
    std::vector<bool> fHistory;

    void UpdateState(unsigned neuron);
    void UpdateOutput(unsigned neuron);

    bool FindPattern() const;

    void ComposeSolution(Solution& solution);

    const PositionList* fPositionList;
    const MoveList* fMoveList;
  };
}
  
#endif /* KTNEURALNETWORK_HH */
