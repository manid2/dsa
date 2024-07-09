/**
 * Bellman-Ford - Single source shortest path to all nodes
 * =======================================================
 *
 * Refer:
 *
 * https://www.w3schools.com/dsa/dsa_algo_graphs_bellmanford.php
 * https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
 */

#include <bits/stdc++.h>

using namespace std;

/* ===========================================================================
 * Data structures
 * ===========================================================================
 */
// Edge is a pair of nodes with weight [u, v, w]
using Edge = array<int, 3>;

// Graph is a pair of V nodes & array of E edges
using Graph = pair<int, vector<Edge>>;

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
class _00_test
{
public:
	_00_test(const string &name) : name(name) {}

	string getName(void) const { return name; }

	virtual vector<int> shortestPaths(const Graph &g, int src = 0) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : Best O(E), Average O(V*E), Worst O(V*E) => O(n^3) when E = V^2
 *      For a complete graph E = V(V-1)/2 => O(E) = O(V^2).
 * SC : O(V) => O(n)
 */
class _01_bellman_ford : public _00_test
{
public:
	_01_bellman_ford()
	    : _00_test("Bellman-Ford single source shortest path to all "
	               "nodes")
	{
	}

	vector<int> shortestPaths(const Graph &g, int src = 0) override
	{
		const int n = g.first;
		vector<int> d(n, INT_MAX);
		d[src] = 0;
		for (int i = 0; i < n - 1; i++)
			for (auto [u, v, w] : g.second)
				if (d[u] != INT_MAX)
					d[v] = min(d[v], d[u] + w);
		// Detect negative cycle
		for (auto [u, v, w] : g.second)
			if (d[u] != INT_MAX && d[v] > d[u] + w)
				return {INT_MIN};
		return d;
	}
};

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
template <class Container = vector<int>>
string _vec2str(const Container &vec)
{
	ostringstream oss;
	using T = Container::value_type;
	oss << "{";
	copy(vec.begin(), vec.end() - 1, ostream_iterator<T>(oss, ", "));
	oss << vec.back();
	oss << "}";
	return oss.str();
}

string _g2str(const Graph &g)
{
	ostringstream oss;
	oss << "{";
	for (int i = 0; auto e : g.second) {
		if (i++) oss << ", ";
		oss << _vec2str<Edge>(e);
	}
	oss << "}";
	return oss.str();
}

void test_impl(const vector<pair<Graph, int>> &ip,
               const vector<vector<int>> &op, shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		vector<int> t = f->shortestPaths(ip[i].first, ip[i].second);
		if (t != op[i]) {
			cerr << f->getName() << " test failed: "
			     << "expected " << _vec2str(op[i]) << ", actual "
			     << _vec2str(t) << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  test-" << i << ":  "
			     << "input: graph = " << _g2str(ip[i].first)
			     << ", source = " << ip[i].second
			     << "  output: nums = " << _vec2str(t) << "\n";
	}
}

int main(int, char **)
{
	Graph g1{4, {{2, 1, -10}, {3, 2, 3}, {0, 3, 5}, {0, 1, 4}}};
	Graph g2{5,
	         {{0, 1, -1},
	          {0, 2, 3},
	          {1, 2, 3},
	          {1, 3, 2},
	          {1, 4, 2},
	          {3, 2, 5},
	          {3, 1, 1},
	          {4, 3, -3}}};
	Graph ng1(g1);
	ng1.second.push_back({1, 3, 5}); // Negative cycle graph

	vector<pair<Graph, int>> ip{
	    {g1, 0},
	    {g2, 0},
	    {ng1, 0},
	};

	vector<vector<int>> op{
	    {0, -2, 8, 5},
	    {0, -1, 2, -2, 1},
	    {INT_MIN}, // Indicate negative cycle is detected in graph
	};

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_bellman_ford>(),
	};

	for (size_t i = 0; i < impls.size(); i++) {
		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "Testing implementation " << i + 1 << " "
			     << impls[i]->getName() << "\n";

		test_impl(ip, op, impls[i]);
	}

	cout << "Executed " << impls.size() << " implementations"
	     << " with " << ip.size() << " tests." << endl;
	return 0;
}
