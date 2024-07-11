/**
 * Dijkstra's - Single source shortest path to all nodes
 * =====================================================
 *
 * Refer:
 *
 * https://www.hackerrank.com/challenges/dijkstrashortreach/problem
 * https://github.com/wj32/Judge/blob/master/HackerRank/Dijkstra-%20Shortest%20Reach%202.cpp
 * https://takeuforward.org/data-structure/dijkstras-algorithm-shortest-distance/
 * https://cp-algorithms.com/graph/dijkstra.html
 */

#include <bits/stdc++.h>

using namespace std;

/* ===========================================================================
 * Data structures
 * ===========================================================================
 */
// Graph is an adjacency list where for each vertex u contains a list of other
// end vertex v and weight w in pair.
using Graph = vector<vector<pair<int, int>>>;

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
class _00_test
{
public:
	_00_test(const string &name) : name(name) {}

	string getName(void) const { return name; }

	virtual void shortestPaths(int n, const vector<vector<int>> &edges,
	                           int src, vector<int> &distances,
	                           vector<int> &predecessors) = 0;

	vector<int> shortestPath(const vector<int> &p, int s, int t)
	{
		vector<int> path;
		for (int v = t; v != s; v = p[v]) path.push_back(v);
		path.push_back(s);
		reverse(path.begin(), path.end());
		return path;
	}

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : Best O(n^2), Average O(n^2), Worst O(n^2)
 * SC : O(1)
 */
class _01_dijkstra_pq : public _00_test
{
public:
	_01_dijkstra_pq()
	    : _00_test("Dijkstra's single source shortest path to all "
	               "nodes using Priority Queue (Heap)")
	{
	}

	void shortestPaths(int n, const vector<vector<int>> &edges, int s,
	                   vector<int> &d, vector<int> &p) override
	{
		// use n + 1 for 1 indexed nodes
		Graph g(n);
		for (size_t i = 0; i < edges.size(); i++) {
			int u = edges[i][0];
			int v = edges[i][1];
			int w = edges[i][2];
			g[u].emplace_back(v, w);

			// skip this for directed graph
			g[v].emplace_back(u, w);
		}
		dijkstras(g, s, d, p);
	}

	void dijkstras(const Graph &g, int s, vector<int> &d, vector<int> &p)
	{
		using pi_t = pair<int, int>;
		using vi_t = vector<pi_t>;
		using pq_t = priority_queue<pi_t, vi_t, greater<pi_t>>;

		const int n = static_cast<int>(g.size());
		d.assign(n, INT_MAX); // distances
		p.assign(n, -1);      // predecessors

		pq_t pq;
		pq.emplace(0, s);
		d[s] = 0;

		while (!pq.empty()) {
			int u = pq.top().second;
			pq.pop();

			for (auto an : g[u]) {
				int v = an.first;
				int w = an.second;

				if (d[v] > d[u] + w) {
					d[v] = d[u] + w;
					p[v] = u;
					pq.emplace(d[v], v);
				}
			}
		}
	}
};

/* ===========================================================================
 * Test code
 * ===========================================================================
 */
using pi_t = pair<int, int>;
using vi_t = vector<pi_t>;
using v1_t = vector<int>;
using ed_t = vector<v1_t>;
using ip_t = tuple<int, ed_t, int, int>;
using op_t = tuple<v1_t, v1_t, v1_t>;

template <class Container = v1_t>
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

string _e2str(const ed_t &edges)
{
	ostringstream oss;
	oss << "{";
	for (int i = 0; const auto &e : edges) {
		if (i++) oss << ", ";
		oss << _vec2str(e);
	}
	oss << "}";
	return oss.str();
}

void test_impl(const vector<ip_t> &ip, const vector<op_t> &op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		const auto &[n, e, s, t] = ip[i];
		const auto &[_d, _p, _path] = op[i];
		vector<int> d, p, path;

		f->shortestPaths(n, e, s, d, p);
		if (d != _d) {
			cerr << f->getName() << " test failed: "
			     << "distances expected " << _vec2str(_d)
			     << ", actual " << _vec2str(d) << "." << endl;
			exit(1);
		}

		if (p != _p) {
			cerr << f->getName() << " test failed: "
			     << "predecessors expected " << _vec2str(_p)
			     << ", actual " << _vec2str(p) << "." << endl;
			exit(1);
		}

		path = f->shortestPath(p, s, t);
		if (path != _path) {
			cerr << f->getName() << " test failed: "
			     << "paths expected " << _vec2str(_path)
			     << ", actual " << _vec2str(path) << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  test-" << i << ":  "
			     << "input: nodes = " << n
			     << ", edges = " << _e2str(e)
			     << ", source = " << s << ", target = " << t
			     << "  output: distances = " << _vec2str(d)
			     << ", predecessors = " << _vec2str(p)
			     << ", path = " << _vec2str(path) << "\n";
	}
}

void _append_test_data_01(vector<ip_t> &ip, vector<op_t> &op)
{
	int n = 5, /*m = 6,*/ s = 0, t = 4;
	ed_t e{{0, 1, 2}, {0, 3, 1}, {1, 2, 4},
	       {1, 4, 5}, {2, 3, 3}, {2, 4, 1}};

	v1_t d{0, 2, 4, 1, 5};
	v1_t p{-1, 0, 3, 0, 2};
	v1_t path{0, 3, 2, 4};

	ip.emplace_back(n, e, s, t);
	op.emplace_back(d, p, path);
}

void _append_test_data_02(vector<ip_t> &ip, vector<op_t> &op)
{
	int n = 4, /*m = 4,*/ s = 0, t = 3;
	ed_t e{{0, 1, 24}, {0, 3, 20}, {2, 0, 3}, {3, 2, 12}};

	v1_t d{0, 24, 3, 15};
	v1_t p{-1, 0, 0, 2};
	v1_t path{0, 2, 3};

	ip.emplace_back(n, e, s, t);
	op.emplace_back(d, p, path);
}

int main(int, char **)
{
	vector<ip_t> ip;
	vector<op_t> op;

	_append_test_data_01(ip, op);
	_append_test_data_02(ip, op);

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_dijkstra_pq>(),
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
