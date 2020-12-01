#include <chrono>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

// Dijkstras Shortest Path Algorithm
// https://www.youtube.com/watch?v=pVfj6mxhdMw&ab_channel=ComputerScience
// To Compile
// c++ --std=c++11 -O3 dijkstra.cc -o dijkstra

struct Edge {
  string a, b;
  int weight;
  Edge() : a{""}, b{""}, weight{0} {}
  Edge(string a, string b, int weight) : a{a}, b{b}, weight{weight} {}
};

ostream& operator<<(ostream& out, const Edge& e) {
  out << "(" << e.a << "," << e.b << "," << e.weight << ")";
  return out;
}

class Graph {
  map<string, list<Edge>> neigh_map;
  unordered_set<string> nodes;

 public:
  Graph() {}
  void add(const string& a, const string& b, int weight) {
    // bi-directional edges
    Edge ab(a, b, weight);
    Edge ba(b, a, weight);
    neigh_map[a].push_back(ab);
    neigh_map[b].push_back(ba);
    nodes.insert(a);
    nodes.insert(b);
  }

  // Dijkstras Shortest Path Algorithm
  list<Edge> find_paths(const string& source_node) {
    // table of shortest distance from source node
    // reuse Edge stricture. a - dest, b - prev node, weight - weight from
    // source to dest.
    map<string, Edge> m;
    // visited nodes
    unordered_set<string> visited;
    // tree of dest nodes sorted by weight from source node to this node.
    set<pair<int, string>> not_visited_by_w;

    // init the table
    for (const string& a : nodes) {
      int w = a == source_node ? 0 : numeric_limits<int>::max();
      m[a] = Edge(a, "", w);
      not_visited_by_w.insert(pair<int, string>(w, a));
    }

    // stop when one unvisited node left
    while (not_visited_by_w.size() > 1) {
      // pop not_visited with min weight;
      auto& vis = *(not_visited_by_w.cbegin());
      int vis_weight = vis.first;
      string vis_name = vis.second;
      not_visited_by_w.erase(vis);
      for (auto& e : neigh_map[vis_name]) {
        if (visited.count(e.b) > 0) {
          continue;
        }
        int new_w = vis_weight + e.weight;
        auto& m_row = m[e.b];
        int old_w = m_row.weight;
        if (new_w < old_w) {
          // better path found
          // update weight and prev_node in the table
          m_row.weight = new_w;
          m_row.b = vis_name;
          // update weight in the tree of nodes sorted by weight
          not_visited_by_w.erase(pair<int, string>(old_w, e.b));
          not_visited_by_w.insert(pair<int, string>(new_w, e.b));
        }
      }
      visited.insert(vis_name);
    }
    list<Edge> li;
    for (auto& v : m) {
      li.push_back(v.second);
    }
    return li;
  }
};

int main(void) {
  Graph g;
  g.add("A", "B", 6);
  g.add("A", "D", 1);
  g.add("B", "D", 2);
  g.add("B", "E", 2);
  g.add("B", "C", 5);
  g.add("E", "D", 1);
  g.add("E", "C", 5);

  const string source_node = "A";
  const auto& t1 = chrono::high_resolution_clock::now();
  list<Edge> paths = g.find_paths(source_node);
  const chrono::duration<double, milli> tt =
      chrono::high_resolution_clock::now() - t1;
  for (Edge e : paths) {
    cout << source_node << " : " << e << endl;
  }
  cout << "Took " << tt.count() << " ms" << endl;
  return 0;
}
