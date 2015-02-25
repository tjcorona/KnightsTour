#ifndef KTTYPEDEFS_HH
#define KTTYPEDEFS_HH

#include <utility>
#include <vector>
#include <ostream>
#include <cassert>

#include "KTAdjacencyList.hh"

namespace KT
{
  extern unsigned gFile;
  extern unsigned gRank;
  
  struct Position
  {
    Position(unsigned p) : position(p) { assert(p<gRank*gFile); }
    Position(char col,unsigned row) : position((col-'a')*gRank + row) {}

    unsigned Row() const { return position%gRank+1; }
    char Column() const { return position/gRank + 'a'; }

    unsigned position;
  };

  inline bool operator==(const Position& p1,const Position& p2)
  {
    return p1.position == p2.position;
  }

  inline std::ostream& operator<<(std::ostream& s,const Position& p)
  {
    s<<"("<< p.Column()<<","<<p.Row()<<")";
    return s;
  }

  typedef edge<Position> Move;

  inline std::ostream& operator<<(std::ostream& s,const Move& m)
  {
    s<<m.first<<"<->"<<m.second;
    return s;
  }

  typedef std::vector<Position> Solution;
  typedef std::vector<Solution> SolutionSet;

}
  
#endif /* KTTYPEDEFS_HH */
