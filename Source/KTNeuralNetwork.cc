#include "KTNeuralNetwork.hh"

#include <cmath>
#include <limits>
#include <iostream>

#include "Random.hh"

namespace KT
{
  Solution NeuralNetwork::FindTour(const KnightGraph& graph,
				   bool requireFullTour)
  {
    fPositionList = &(graph.GetPositionList());
    fMoveList = &(graph.GetMoveList());
    Solution solution;
    bool fullTour = false;

    unsigned attempts = 0;

    do
    {
      solution.clear();

      fState.assign((*fMoveList).size(),0);
      fOutput.assign((*fMoveList).size(),false);
      for (unsigned i=0;i<(*fMoveList).size();i++)
	fOutput[i] = Random::GetInstance().Uniform(2);
      fHistory.assign((*fMoveList).size()*fHistoryLength,false);
    
      fStable = false;

      fIteration = 0;
      while (!fStable)
      {
	fStable = true;
	for (unsigned i=0;i<(*fMoveList).size();i++)
	  UpdateState(i);
	for (unsigned i=0;i<(*fMoveList).size();i++)
	  UpdateOutput(i);
	fIteration++;
	if (fIteration > fMaxIterations)
	  break;
      }

      attempts++;
      
      if (fStable)
      {
	std::cout<<"Attempt # "<<attempts<<std::endl;
	std::cout<<"Stable @ iteration "<<fIteration<<std::endl;
	ComposeSolution(solution);
	std::cout<<"length of tour: "<<solution.size()<<std::endl;
      }
    }
    while (FindPattern() || solution.empty() || (requireFullTour && solution.size() != (*fPositionList).size()+1));

    std::cout<<"Convergent!"<<std::endl;

    return solution;
  }

  void NeuralNetwork::UpdateState(unsigned neuron)
  {
    int previous_state = fState[neuron];

    fState[neuron] += 4;
    for (unsigned i=0;i<(*fMoveList)[neuron].neighbors();i++)
      fState[neuron] -= fOutput[(*fMoveList)[neuron][i].index];
    fState[neuron] -= 2*fOutput[neuron];

    if (previous_state != fState[neuron])
      fStable = false;
  }

  void NeuralNetwork::UpdateOutput(unsigned neuron)
  {
    int previous_output = fOutput[neuron];

    if (fState[neuron] > 3)
      fOutput[neuron] = 1;
    else if (fState[neuron] < 0)
      fOutput[neuron] = 0;

    if (previous_output != fOutput[neuron])
      fStable = false;

    fHistory[fIteration%fHistoryLength + neuron] = fOutput[neuron];
  }

  bool NeuralNetwork::FindPattern() const
  {
    unsigned len = (fIteration < fHistoryLength ? fIteration : fHistoryLength);

    std::vector<bool> pattern(len,true);

    for (unsigned i=0;i<(*fMoveList).size();i++)
    {
      for (int j=len;j>=0;j--)
      {
	pattern[j] = (pattern[j] && fHistory[(*fMoveList).size()*j + i]);
      }
    }

    bool ret = true;
    for (unsigned i=0;i<len;i++)
      ret &= pattern[i];
    
    return ret;
  }

  void NeuralNetwork::ComposeSolution(Solution& solution)
  {
    unsigned startPosition = 0;
    unsigned currentPosition = startPosition;
    solution.push_back((*fPositionList)[currentPosition]);
    do
    {
      for (unsigned i=0;i<fOutput.size();i++)
      {
    	if (fOutput[i] == 1)
    	{
    	  if ((*fMoveList)[i].first.position == currentPosition)
    	  {
    	    currentPosition = (*fMoveList)[i].second.position;
    	    fOutput[i] = 0;
    	    break;
    	  }

    	  if ((*fMoveList)[i].second.position == currentPosition)
    	  {
    	    currentPosition = (*fMoveList)[i].first.position;
    	    fOutput[i] = 0;
    	    break;
    	  }
    	}
      }
      solution.push_back((*fPositionList)[currentPosition]);
    }
    while (currentPosition!=startPosition);

    return;
  }
}
