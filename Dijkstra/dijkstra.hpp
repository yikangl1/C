#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>                    //Biggest int: std::numeric_limits<int>::max()
#include "array_queue.hpp"
#include "array_stack.hpp"
#include "heap_priority_queue.hpp"
#include "hash_graph.hpp"


namespace ics {

class Info {
  public:
    Info() { }

    Info(std::string a_node) : node(a_node) { }

    bool operator==(const Info &rhs) const { return cost == rhs.cost && from == rhs.from; }

    bool operator!=(const Info &rhs) const { return !(*this == rhs); }

    friend std::ostream &operator<<(std::ostream &outs, const Info &i) {
      outs << "Info[" << i.node << "," << i.cost << "," << i.from << "]";
      return outs;
    }

    //Public instance variable definitions
    std::string node = "?";
    int cost = std::numeric_limits<int>::max();
    std::string from = "?";
  };


  bool gt_info(const Info &a, const Info &b) { return a.cost < b.cost; }

  typedef ics::HashGraph<int>                   DistGraph;
  typedef ics::HeapPriorityQueue<Info, gt_info> CostPQ;
  typedef ics::HashOpenMap<std::string, Info>   CostMap;
  typedef ics::pair<std::string, Info>          CostMapEntry;


//Return the final_map as specified in the lecture-note description of
//  extended Dijkstra algorithm
  CostMap extended_dijkstra(const DistGraph &g, std::string start_node) {
        CostMap Backup_Map(1, DistGraph::hash_str);
        CostMap Result_Map(1, DistGraph::hash_str);
        CostPQ Backup_pq;
        CostPQ info_pq;
        CostMap info_map(1, DistGraph::hash_str);
        CostMap answer_map(1, DistGraph::hash_str);
        for(auto kv: g.all_nodes())
        {
            info_map[kv.first] = Info(kv.first);
            Backup_Map[kv.first] = Info(kv.first);
        }
        info_map[start_node].cost = 0;
        for(auto kv: info_map)
        {
            info_pq.enqueue(kv.second);
            Backup_pq.enqueue(kv.second);
        }
        if (Backup_Map.size())
        {
            Info temp = Info();
        }
        else
        {
            Info temp = Info();
        }
        while(info_map.size())
        {
            Info data;
            data = Info();
            while(answer_map.has_key(data.node) ||  data.node == "?")
            {

                if(info_pq.size() == 0)
                {
                    break;
                }
                data = info_pq.dequeue();
            }

            if(data.cost == std::numeric_limits<int>::max())
            {
                return answer_map;
            }
            auto min_node = data.node;
            auto min_cost = data.cost;
            auto min_backup_node = data.node;
            auto min_backup_cost = data.cost;
            info_map.erase(min_node);
            answer_map[min_node] = data;
            info_pq.clear();
            for(auto kv: g.out_edges(min_node))
            {
                if(answer_map.has_key(kv.second))
                {
                    Backup_Map[kv.second].cost = Backup_Map[kv.second].cost + 1;
                    Backup_Map[kv.second].from = 1;
                    if (Backup_Map[kv.second].cost == 0 )
                    {
                        Backup_Map[kv.second].cost = Backup_Map[kv.second].cost + 1;
                    }
                    else
                    {
                        Backup_Map[kv.second].cost =  1;
                    }
                }
                else if(!answer_map.has_key(kv.second))
                {
                    if (info_map[kv.second].cost > min_cost + g.edge_value(min_node,kv.second)  || info_map[kv.second].cost == std::numeric_limits<int>::max()  )
                    {
                        info_map[kv.second].cost = g.edge_value(min_node,kv.second) + min_cost;
                        info_map[kv.second].from = min_node;
                    }
                }
                info_pq.enqueue(info_map[kv.second]);
            }
        }
        return answer_map;
  }


//Return a queue whose front is the start node (implicit in answer_map) and whose
//  rear is the end node
  ArrayQueue <std::string> recover_path(const CostMap &answer_map, std::string end_node) {
        ArrayQueue<std::string> result;
        ArrayStack<std::string> stack;
        ArrayStack<std::string> Backup_stack;
        ArrayQueue<std::string> temp;

        while(end_node != "?")
        {
            stack.push(end_node);
            end_node = answer_map[end_node].from;
        }
        while(!stack.empty())
        {
            result.enqueue(stack.pop());
        }
        return result;
  }


}

#endif /* DIJKSTRA_HPP_ */
