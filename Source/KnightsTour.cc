#include <iostream>
#include <unistd.h>

#include "KTTypeDefs.hh"
#include "KTDisplay.hh"
#include "KTKnightGraph.hh"
#include "KTNeuralNetwork.hh"

using namespace KT;

int main(int /*argc*/,char** /*argv*/)
{
  unsigned boardSize = 6;

  gRank = boardSize;
  gFile = boardSize;

  // gRank = 3;
  // gFile = 4;

  // {
  //   Solution s;

  //   for (unsigned i=0;i<KT::gRank*KT::gFile;i++)
  //     s.push_back(Position(i));
  
  //   PrintSolution(s,4.);
  // }
  
  // {
  //   KnightGraph graph;

  //   // graph.Print();
  //   // PrintKnightGraph(graph,4.);

  //   for (unsigned i=0;i<graph.GetMoveList().size();i++)
  //   {
  //     std::cout<<graph.GetMoveList()[i].index<<" : ";
  //     for (unsigned j=0;j<graph.GetMoveList()[i].neighbors();j++)
  //     {
  // 	std::cout<<graph.GetMoveList()[i][j].index<<" ";
  //     }
  //     std::cout<<std::endl;
  //   }

  //   // for (unsigned i=0;i<graph.GetMoveList().size();i++)
  //   // {
  //   //   std::cout<<graph.GetMoveList()[i]<<" : ";
  //   //   for (unsigned j=0;j<graph.GetMoveList()[i].neighbors();j++)
  //   //   {
  //   // 	std::cout<<graph.GetMoveList()[i][j]<<" ";
  //   //   }
  //   //   std::cout<<std::endl;
  //   // }

  //   // PrintKnightGraph2(graph,5.e-1);
  // }

  {
    KnightGraph graph;
    NeuralNetwork neuralNetwork;
    Solution solution = neuralNetwork.FindTour(graph);
    PrintSolution(solution,2.);
  }
  
  return 0;
}
