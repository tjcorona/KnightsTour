#ifndef KTDISPLAY_HH
#define KTDISPLAY_HH

#include <string>

#include "KTTypeDefs.hh"
#include "KTKnightGraph.hh"

namespace KT
{
  std::string Board();
  void PrintBoard();
  int RowOf(const Position& p);
  int ColumnOf(const Position& p);
  void PrintPosition(const Position& p,const char symbol='X');
  void PrintMove(const Move& p,const char symbol1='X',const char symbol2='X');
  void PrintKnightGraph(const KnightGraph& graph,double frequency=1.);
  void PrintKnightGraph2(const KnightGraph& graph,double frequency=1.);
  void PrintSolution(const Solution& s,double frequency=1.);
}

#endif /* KTDISPLAY_HH */
