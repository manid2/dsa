#pragma once

#include "common.h"

/*
 * Graphs
 * ======
 *
 * Data structures and helper functions
 */

namespace Graphs {
const int X = std::numeric_limits<int>::max();
const int NX = std::numeric_limits<int>::min();

inline vi2_t edges2mat(const int n, const vi2_t &edges) {
  // convert list of edges to adjacency matrix
  vi2_v(g, n, X);
  for (size_t i = 0; i < edges.size(); i++) {
    int u = edges[i][0];
    int v = edges[i][1];
    int w = edges[i][2];
    g[u][v] = w;

    // skip this for directed graph
    g[v][u] = w;
  }
  return g;
}

inline vi_t shortestPath(const vi_t &parent, int source, int target) {
  vi_t p;
  for (int u = target; u != source; u = parent[u])
    p.push_back(u);
  p.push_back(source);
  reverse(begin(p), end(p));
  return p;
}

inline string to_string(const vi_t &c) {
  ostringstream out;
  out << "{";
  for (int i = 0; const int e : c) {
    out << (i++ ? ", " : "");
    if (e == X)
      out << "x";
    else if (e == NX)
      out << "-x";
    else
      out << e;
  }
  out << "}";
  return out.str();
}

inline string to_string(const vi2_t &g) {
  ostringstream out;
  const int n = size(g);
  out << "{";
  for (int i = 0; i < n; i++) {
    out << to_string(g[i]);
    if (i < n - 1)
      out << ", ";
  }
  out << "}";
  return out.str();
}

inline string to_string(int nodes, const vi2_t &edges) {
  return format("nodes = {}, edges = {}", nodes, to_string(edges));
}
} // namespace Graphs