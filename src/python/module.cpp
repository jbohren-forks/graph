#include "basic_graph.cpp"
#include "graph.hpp"
#include "digraph.hpp"
#include <boost/python.hpp>

namespace boost { namespace graph { namespace python {

extern void export_Graph();
extern void export_Digraph();
extern void export_betweenness_centrality();
extern void export_page_rank();
extern void export_done();
extern void export_breadth_first_search();
extern void export_dijkstra_shortest_paths();
template<typename Graph> void export_breadth_first_search_in_graph();
template<typename Graph> void export_dijkstra_shortest_paths_in_graph();

template<typename Graph>
void export_in_graph()
{
  export_breadth_first_search_in_graph<Graph>();
  export_dijkstra_shortest_paths_in_graph<Graph>();
}

BOOST_PYTHON_MODULE(bgl)
{
  enum_<graph_file_kind>("file_kind")
    .value("adjlist", gfk_adjlist)
    .value("graphviz", gfk_graphviz)
    ;

  export_Graph();
  export_Digraph();
  export_betweenness_centrality();
  export_page_rank();
  export_done();
  export_breadth_first_search();
  export_dijkstra_shortest_paths();
}

template void export_in_graph<Graph>();
template void export_in_graph<Digraph>();

} } } // end namespace boost::graph::python
