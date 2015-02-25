#include "KTDisplay.hh"

#include <cmath>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include <ncurses.h>

namespace KT
{

  std::string Board()
  {
    std::stringstream s;
    for (unsigned int i=0;i<KT::gRank;i++)
    {
      s<<std::endl<<" ---";
      for (unsigned int j=0;j<KT::gFile-1;j++)
	s<<" ---";
      s<<std::endl<<"|";
      for (unsigned int j=0;j<KT::gFile;j++)
	s<<"   |";
    }
    s<<std::endl<<" ---";
    for (unsigned int j=0;j<KT::gFile-1;j++)
      s<<" ---";
    s<<std::endl<<std::endl;
    return s.str();
  }

  void PrintBoard()
  {
    initscr();
    erase();
    printw(Board().c_str());
    refresh();
    usleep(1.e6);
    endwin();
  }

  int RowOf(const Position& p)
  {
    return (KT::gRank - (p.Row() - 1))*2;
  }

  int ColumnOf(const Position& p)
  {
    return 2 + (p.Column()-'a')*4;
  }

  void PrintPosition(const Position& p,const char symbol)
  {
    mvprintw(RowOf(p),ColumnOf(p),"%c",symbol);
    refresh();
  }

  void PrintMove(const Move& m,const char symbol1,const char symbol2)
  {
    PrintPosition(m.first,symbol1);
    PrintPosition(m.second,symbol2);
  }

  void PrintKnightGraph(const KnightGraph& graph,double frequency)
  {
    initscr();
    erase();
    printw(Board().c_str());

    unsigned usec = (1./frequency)*1.e6;

    unsigned maxSpacing = 1;

    while ((KT::gRank*KT::gFile)/pow(10,maxSpacing)>1.)
      maxSpacing++;
      
    const adjacency_list<Position>& list = graph.GetPositionList();

    int counter = 0;
    for (int i=0;i<list.size();i++)
    {
      std::stringstream s;
      s<<"Position "<<std::setw(maxSpacing)<<++counter<<": "<<list.at(i)<<": ";
      for (unsigned j=0;j<list.at(i).neighbors();j++)
      {
	s<<list.at(i).at(j);
	if (j!=list.at(i).neighbors()-1)
	  s<<", ";
      }
      mvprintw(0,0,"%s",s.str().c_str());

      PrintPosition(list.at(i));
      for (unsigned j=0;j<list.at(i).neighbors();j++)
	PrintPosition(list.at(i).at(j),'O');
      usleep(usec);
      PrintPosition(list.at(i),' ');

      // clear what was just printed
      for (unsigned j=0;j<list.at(i).neighbors();j++)
	PrintPosition(list.at(i).at(j),' ');
      mvprintw(0,0,"%s",std::string(s.str().size(),' ').c_str());
    }
    endwin();
  }

  void PrintKnightGraph2(const KnightGraph& graph,double frequency)
  {
    initscr();
    erase();
    printw(Board().c_str());

    unsigned usec = (1./frequency)*1.e6;

    unsigned maxSpacing = 1;

    while ((KT::gRank*KT::gFile)/pow(10,maxSpacing)>1.)
      maxSpacing++;
      
    const adjacency_list<Move>& list = graph.GetMoveList();

    int counter = 0;
    for (int i=0;i<list.size();i++)
    {
      std::stringstream s;
      s<<"Move "<<std::setw(maxSpacing)<<++counter<<": "<<list.at(i)<<": ";
      for (unsigned j=0;j<list.at(i).neighbors();j++)
      {
	s<<list.at(i).at(j);
	if (j!=list.at(i).neighbors()-1)
	  s<<",";
      }
      mvprintw(0,0,"%s",s.str().c_str());

      for (unsigned j=0;j<list.at(i).neighbors();j++)
	PrintMove(list.at(i).at(j),'O','O');
      PrintMove(list.at(i));
      usleep(usec);
      PrintMove(list.at(i),' ',' ');

      // clear what was just printed
      for (unsigned j=0;j<list.at(i).neighbors();j++)
	PrintMove(list.at(i).at(j),' ',' ');
      mvprintw(0,0,"%s",std::string(s.str().size(),' ').c_str());
    }
    endwin();
  }

  void PrintSolution(const Solution& s,double frequency)
  {
    initscr();
    erase();
    printw(Board().c_str());

    unsigned usec = (1./frequency)*1.e6;

    unsigned maxSpacing = 1;

    while ((KT::gRank*KT::gFile)/pow(10,maxSpacing)>1.)
      maxSpacing++;
      
    int offset = 0;
    int counter = 0;
    for (Solution::const_iterator it=s.begin();it!=s.end();++it)
    {
      std::stringstream s;
      s<<"Position "<<std::setw(maxSpacing)<<++counter<<": "<<*it;
      mvprintw(0,0,"%s",s.str().c_str());

      PrintPosition(*it,'1'+offset);
      usleep(usec);
    }
    timeout(-1);
    int c = getch();
    endwin();
  }
}
