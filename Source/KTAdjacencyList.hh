#ifndef KTADJACENCYLIST_HH
#define KTADJACENCYLIST_HH

#include <algorithm>
#include <vector>

template <class T>
class adjacency_list_vertex;

// template <class T>
// using edge = std::pair<adjacency_list_vertex<T>&,adjacency_list_vertex<T>&>;

template <class T>
struct edge : public std::pair<adjacency_list_vertex<T>&,
			      adjacency_list_vertex<T>&>
{
  typedef std::pair<adjacency_list_vertex<T>&,
		    adjacency_list_vertex<T>&> pair;
  edge(const pair& p) : pair(p), index(0) {}
  int index;
};

template <class T, class Alloc = std::allocator<T> >
using adjacency_list = typename std::vector<adjacency_list_vertex<T>, typename Alloc::template rebind<adjacency_list_vertex<T> >::other>;

template <class T, class Alloc = std::allocator<T> >
using edge_adjacency_list = adjacency_list<edge<T>,Alloc>;

template <typename Iterator>
void make_adjacency(Iterator first, Iterator second);

template <typename Iterator>
void remove_adjacency(Iterator first, Iterator second);

template <class T>
class adjacency_list_vertex : public T
{
public:
  typedef adjacency_list_vertex vertex;
  template <class Iterator>
  friend void make_adjacency(Iterator first, Iterator second);
  template <class Iterator>
  friend void remove_adjacency(Iterator first, Iterator second);

  typedef std::vector<adjacency_list_vertex*> vertex_p_vector;

  adjacency_list_vertex() : T() {}
  adjacency_list_vertex(const T& t) : T(t) {}
  virtual ~adjacency_list_vertex() {}
    
  unsigned neighbors() const { return fNeighbors.size(); }

  vertex& at(unsigned i) { return *(fNeighbors.at(i)); }
  const vertex& at(unsigned i) const { return *(fNeighbors.at(i)); }
  vertex& operator[](unsigned i) { return *(fNeighbors[i]); }
  const vertex& operator[](unsigned i) const { return *(fNeighbors[i]); }

private:
  vertex_p_vector fNeighbors;
};

template <typename Iterator>
void make_adjacency(Iterator first, Iterator second)
{
  if (first != second)
  {
    if (std::find((*first).fNeighbors.begin(),(*first).fNeighbors.end(),&(*second))==(*first).fNeighbors.end())
      (*first).fNeighbors.push_back(&(*second));
    if (std::find((*second).fNeighbors.begin(),(*second).fNeighbors.end(),&(*first))==(*second).fNeighbors.end())
      (*second).fNeighbors.push_back(&(*first));
  }
}

template <typename Iterator>
void remove_adjacency(Iterator first, Iterator second)
{
  (*first).fNeighbors.erase(std::remove((*first).fNeighbors.begin(),
				     (*first).fNeighbors.end(),
				     &(*second)),
			 (*first).fNeighbors.end());
  (*second).fNeighbors.erase(std::remove((*second).fNeighbors.begin(),
				     (*second).fNeighbors.end(),
				     &(*first)),
			 (*second).fNeighbors.end());
}

template <class T, class Alloc>
edge_adjacency_list<T,Alloc> edge_list(adjacency_list<T,Alloc>& list)
{
  typedef edge_adjacency_list<T,Alloc> c_list;

  c_list list_c;

  unsigned idx = 0;

  for (unsigned i=0;i<list.size();i++)
  {
    for (unsigned j=0;j<list[i].neighbors();j++)
    {
      edge<T> p1(typename edge<T>::pair(list[i],list[i][j]));
      edge<T> p2(typename edge<T>::pair(list[i][j],list[i]));

      if (std::find(list_c.begin(),list_c.end(),p1) == list_c.end() &&
	  std::find(list_c.begin(),list_c.end(),p2) == list_c.end())
      {
	p1.index = idx++;
	list_c.push_back(p1);
      }
    }
  }

  typename c_list::iterator it1,it2;
  for (it1=list_c.begin();it1!=list_c.end();++it1)
  {
    for (it2=it1+1;it2!=list_c.end();++it2)
    {
      if ((*it1).first == (*it2).first ||
	  (*it1).first == (*it2).second ||
	  (*it1).second == (*it2).first ||
	  (*it1).second == (*it2).second)
	make_adjacency(it1,it2);
    }
  }
	  
  return list_c;
}

#endif /* KTADJACENCYLIST_HH */
