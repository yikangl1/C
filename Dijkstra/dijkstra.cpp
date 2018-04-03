#include <string>
#include <iostream>
#include <fstream>
#include "ics46goody.hpp"
#include "array_queue.hpp"
#include "hash_graph.hpp"
#include "dijkstra.hpp"

std::string get_node_in_graph(const ics::DistGraph& g, std::string prompt, bool allow_QUIT) {
  std::string node;
  for(;;) {
    node = ics::prompt_string(prompt + " (must be in graph" + (allow_QUIT ? " or QUIT" : "") + ")");
    if ( (allow_QUIT && node == "QUIT") || g.has_node(node) )
      break;
  }
  return node;
}


int main() {
  try {
      std::ifstream file;
      ics::DistGraph graph;
      std::string s;
      std::string t;
      ics::safe_open(file,"Enter graph file name","flightcost.txt");
      graph.load(file,";");
      std::cout << graph;
      s = get_node_in_graph(graph, "Enter start node", false);
      auto map = ics::extended_dijkstra(graph,s);
      std::cout << map << std::endl;
      std::cout << std::endl;


      s = get_node_in_graph(graph, "Enter stop node", true);
      while(s != "QUIT")
      {
          std::cout << "Cost is ";
          std::cout << map[s].cost;
          std::cout << "; path is ";
          std::cout << ics::recover_path(map,s) << std::endl;
          std::cout << std::endl;
          s = get_node_in_graph(graph, "Enter stop node", true);
      }
  } catch (ics::IcsError& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
