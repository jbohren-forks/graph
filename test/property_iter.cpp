//=======================================================================
// Copyright 2002 Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// This file is part of the Boost Graph Library
//
// You should have received a copy of the License Agreement for the
// Boost Graph Library along with the software; see the file LICENSE.
//
// Permission to modify the code and to distribute modified code is
// granted, provided the text of this NOTICE is retained, a notice that
// the code was modified is included with the above COPYRIGHT NOTICE and
// with the COPYRIGHT NOTICE in the LICENSE file, and that the LICENSE
// file is distributed with the modified code.
//
// LICENSOR MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.
// By way of example, but not limitation, Licensor MAKES NO
// REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY
// PARTICULAR PURPOSE OR THAT THE USE OF THE LICENSED SOFTWARE COMPONENTS
// OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS
// OR OTHER RIGHTS.
//=======================================================================

#include <boost/config.hpp>

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

#define VERBOSE 0

#include <boost/utility.hpp>
#include <boost/graph/property_iter_range.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/random.hpp>
#include <boost/pending/indirect_cmp.hpp>

#include <boost/random/mersenne_twister.hpp>


enum vertex_id_t { vertex_id = 500 };
enum edge_id_t { edge_id = 501 };
namespace boost {
  BOOST_INSTALL_PROPERTY(vertex, id);
  BOOST_INSTALL_PROPERTY(edge, id);
}


#include "graph_type.hpp" // this provides a typedef for Graph

using namespace boost;

/*
  This program tests the property range iterators
 */

using std::cout;
using std::endl;
using std::cerr;
using std::find;


int main(int, char* [])
{
  int ret = 0;
  std::size_t N = 5, E = 0;

  Graph g;
  typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
  typedef boost::graph_traits<Graph>::edge_descriptor Edge;

  int i, j;
  std::size_t current_vertex_id = 0;
  std::size_t current_edge_id = 0;

  property_map<Graph, vertex_id_t>::type vertex_id_map = get(vertex_id, g);

  property_map<Graph, edge_id_t>::type edge_id_map = get(edge_id, g);

  for (std::size_t k = 0; k < N; ++k)
    add_vertex(current_vertex_id++, g);

  // also need to test EdgeIterator graph constructor -JGS
  mt19937 gen;

  for (j=0; j < 10; ++j) {

    // add_edge
#if VERBOSE
    cerr << "Testing add_edge ..." << endl;
#endif
    for (i=0; i < 6; ++i) {
      Vertex a, b;
      a = random_vertex(g, gen);
      do {
        b = random_vertex(g, gen);
      } while ( a == b ); // don't do self edges
#if VERBOSE
      cerr << "add_edge(" << vertex_id_map[a] << "," << vertex_id_map[b] <<")" << endl;
#endif
      Edge e;
      bool inserted;
      boost::tie(e, inserted) = add_edge(a, b, current_edge_id++, g);
#if VERBOSE
      std::cout << "inserted: " << inserted << std::endl;
      std::cout << "source(e,g)" << source(e,g) << endl;
      std::cout << "target(e,g)" << target(e,g) << endl;
      std::cout << "edge_id[e] = " << edge_id_map[e] << std::endl;
      print_edges2(g, vertex_id_map, edge_id_map);
      print_graph(g, vertex_id_map);
      std::cout << "finished printing" << std::endl;
      //      print_in_edges(g, vertex_id_map);
#endif
      }
      ++E;
    }

  typedef boost::graph_property_iter_range< Graph, vertex_id_t>::const_iterator    TNodeConstIterator;
  typedef boost::graph_property_iter_range< Graph, vertex_id_t>::const_type        TNodeConstIteratorType;

  typedef boost::graph_property_iter_range< Graph, vertex_id_t>::iterator    TNodeIterator;
  typedef boost::graph_property_iter_range< Graph, vertex_id_t>::type        TNodeIteratorType;

  typedef boost::graph_property_iter_range< Graph, edge_id_t>::const_iterator    TLinkConstIterator;
  typedef boost::graph_property_iter_range< Graph, edge_id_t>::const_type        TLinkConstIteratorType;

  typedef boost::graph_property_iter_range< Graph, edge_id_t>::iterator    TLinkIterator;
  typedef boost::graph_property_iter_range< Graph, edge_id_t>::type        TLinkIteratorType;

  typedef std::pair<TLinkConstIterator, TLinkConstIterator> tLinkConstIteratorPair;

  TLinkIterator itEdgeBegin, itEdgeEnd;

  tie(itEdgeBegin, itEdgeEnd) = get_property_iter_range(g, edge_id);

  cout << "Edge iteration:" << endl;
  for (; itEdgeBegin != itEdgeEnd; ++itEdgeBegin)
  {
      cout << *itEdgeBegin;
  }
  cout << endl;

  TNodeIterator itVertexBegin, itVertexEnd;

  tie(itVertexBegin, itVertexEnd) = get_property_iter_range(g, vertex_id);

  cout << "Vertex iteration:" << endl;
  for (; itVertexBegin != itVertexEnd; ++itVertexBegin)
  {
      cout << *itVertexBegin;
  }
  cout << endl;

  
  return ret;
}
