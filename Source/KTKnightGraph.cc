#include "KTKnightGraph.hh"

#include <cmath>
#include <limits>
#include <iostream>

namespace KT
{
  KnightGraph::KnightGraph()
  {
    // determine the number of positions
    unsigned size = KT::gRank*KT::gFile;

    // populate the position list
    for (unsigned i=0;i<size;i++)
      fPositions.push_back(Position(i));

    // link position pairs and populate move list
    {
      PositionList::iterator it1,it2;
      for (it1=fPositions.begin();it1!=fPositions.end();++it1)
      {
	for (it2=it1+1;it2!=fPositions.end();++it2)
	{
	  if (Neighbor(it1,it2))
	    make_adjacency<PositionList::iterator>(it1,it2);
	}
      }
    }
    
    fMoves = edge_list<Position,std::allocator<Position> >(fPositions);
  }

  bool KnightGraph::Neighbor(PositionList::iterator position1,
			     PositionList::iterator position2)
  {
    int row1 = (*position1).position%KT::gRank;
    int col1 = (*position1).position/KT::gRank;

    int row2 = (*position2).position%KT::gRank;
    int col2 = (*position2).position/KT::gRank;

    if (col1 - 2 == col2 && row1 - 1 == row2) return true;
    if (col1 - 2 == col2 && row1 + 1 == row2) return true;
    if (col1 - 1 == col2 && row1 - 2 == row2) return true;
    if (col1 - 1 == col2 && row1 + 2 == row2) return true;
    if (col1 + 1 == col2 && row1 - 2 == row2) return true;
    if (col1 + 1 == col2 && row1 + 2 == row2) return true;
    if (col1 + 2 == col2 && row1 - 1 == row2) return true;
    if (col1 + 2 == col2 && row1 + 1 == row2) return true;

    return false;
  }
}
