#ifndef KTKNIGHTGRAPH_HH
#define KTKNIGHTGRAPH_HH

#include "KTTypeDefs.hh"
#include "KTAdjacencyList.hh"

namespace KT
{
  typedef adjacency_list<Position> PositionList;
  typedef edge_adjacency_list<Position> MoveList;

  class KnightGraph
  {
  public:

    KnightGraph();
    virtual ~KnightGraph() {}

    PositionList& GetPositionList() { return fPositions; }
    const PositionList& GetPositionList() const { return fPositions; }

    MoveList& GetMoveList() { return fMoves; }
    const MoveList& GetMoveList() const { return fMoves; }

  private:
    bool Neighbor(PositionList::iterator position1,
		  PositionList::iterator position2);

    PositionList fPositions;
    MoveList fMoves;
  };
}
  
#endif /* KTKNIGHTGRAPH_HH */
