/**
 * Floyd-Warshall - All pairs shortest paths
 * =========================================
 *
 * Refer:
 *
 * https://www.programiz.com/dsa/floyd-warshall-algorithm
 */

#include <bits/stdc++.h>

using namespace std;

/* ===========================================================================
 * Data structures
 * ===========================================================================
 */
// Graph is a V * V matrix where V is number of nodes
using Graph = vector<vector<int>>;

/* ===========================================================================
 * Test helpers
 * ===========================================================================
 */
class _00_test
{
public:
	_00_test(const string &name) : name(name) {}

	string getName(void) const { return name; }

	virtual Graph shortestPaths(Graph g) = 0;

private:
	string name;
};

/* ===========================================================================
 * Algorithms implementation
 * ===========================================================================
 */

/* TC : O(V^3)
 * SC : O(V^2)
 */
class _01_floy_warshall : public _00_test
{
public:
	_01_floy_warshall()
	    : _00_test("Floyd-Warshall all pairs shortest paths")
	{
	}

	void update(Graph &g, int k, int i, int j)
	{
		if (g[i][k] != INT_MAX && g[k][j] != INT_MAX)
			g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	}

	Graph shortestPaths(Graph g) override
	{
		const int n = static_cast<int>(g.size());
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					update(g, k, i, j);
		return g;
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
	for (int i = 0; auto e : g) {
		if (i++) oss << ", ";
		oss << _vec2str(e);
	}
	oss << "}";
	return oss.str();
}

void test_impl(const vector<Graph> &ip, const vector<Graph> &op,
               shared_ptr<_00_test> f)
{
	for (size_t i = 0; i < ip.size(); i++) {
		Graph t = f->shortestPaths(ip[i]);
		if (t != op[i]) {
			cerr << f->getName() << " test failed: "
			     << "expected " << _g2str(op[i]) << ", actual "
			     << _g2str(t) << "." << endl;
			exit(1);
		}

		if (getenv("SHOW_TEST_OUTPUT"))
			cout << "  test-" << i << ":  "
			     << "input: graph = " << _g2str(ip[i])
			     << "  output: shortestDist = " << _g2str(t)
			     << "\n";
	}
}

int main(int, char **)
{
	const int x = INT_MAX;
	vector<Graph> ip{
	    {
	        {0, 3, x, 7},
	        {8, 0, 2, x},
	        {5, x, 0, 1},
	        {2, x, x, 0},
	    },
	    {
	        {0, 5, x, 10},
	        {x, 0, 3, x},
	        {x, x, 0, 1},
	        {x, x, x, 0},
	    },
	    {
	        {0, 3, x, 5},
	        {2, 0, x, 4},
	        {x, 1, 0, x},
	        {x, x, 2, 0},
	    },
	};

	vector<Graph> op{
	    {
	        {0, 3, 5, 6},
	        {5, 0, 2, 3},
	        {3, 6, 0, 1},
	        {2, 5, 7, 0},
	    },
	    {
	        {0, 5, 8, 9},
	        {x, 0, 3, 4},
	        {x, x, 0, 1},
	        {x, x, x, 0},
	    },
	    {
	        {0, 3, 7, 5},
	        {2, 0, 6, 4},
	        {3, 1, 0, 5},
	        {5, 3, 2, 0},
	    },
	};

	vector<shared_ptr<_00_test>> impls{
	    make_shared<_01_floy_warshall>(),
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
