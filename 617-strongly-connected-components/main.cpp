#include <vector>
#include <utility>
#include <stack>
#include <algorithm>
#include <iostream>

using namespace std;

class Kosaraju {
public:
	Kosaraju(int n, vector<pair<int, int>> edge) {
		node_num = n;
		adj.resize(node_num);
		for (auto it = edge.begin(); it != edge.end(); it++)
			adj[it->first].push_back(it->second);
	}

	void excute_kosaraju() {
		visited.resize(node_num);
		fill(visited.begin(), visited.end(), false);
		for (int i = 0; i < node_num; i++)
			if (!visited[i])
				dfs(i);
		transpose_graph();
		fill(visited.begin(), visited.end(), false);
		while (!kosa_stack.empty()) {
			int node = kosa_stack.top();
			kosa_stack.pop();
			if (!visited[node]) {
				vector<int> conn;
				dfs_getscc(node, conn);
				scc.push_back(conn);
			}
		}
	}

	void print_scc() {
		for (auto conn = scc.begin(); conn != scc.end(); conn++) {
			for (auto n = conn->begin(); n != conn->end(); n++)
				cout << *n << " ";
			cout << endl;
		}
	}

	vector<vector<int>> get_scc() {
		return scc;
	}

private:
	int node_num;
	vector<vector<int>> adj;
	vector<vector<int>> transpose_adj;
	vector<vector<int>> scc;
	vector<bool> visited;
	stack<int> kosa_stack;

	void dfs(int node) {
		visited[node] = true;
		for (auto it = adj[node].begin(); it != adj[node].end(); it++)
			if (!visited[*it])
				dfs(*it);
		kosa_stack.push(node);
	}

	void transpose_graph() {
		transpose_adj.resize(node_num);
		for (int i = 0; i < node_num; i++)
			for (auto it = adj[i].begin(); it != adj[i].end(); it++)
				transpose_adj[*it].push_back(i);
	}

	void dfs_getscc(int node, vector<int> &conn) {
		visited[node] = true;
		for (auto it = transpose_adj[node].begin(); it != transpose_adj[node].end(); it++)
			if (!visited[*it])
				dfs_getscc(*it, conn);
		conn.push_back(node);
	}
};

int main() {
	vector<pair<int, int>> edge{ {0,1}, {2,0}, {1,2}, {2,1}, {1,5}, {5,4}, {4,5}, {3,4} };
	int node = 6;
	Kosaraju kosa(node, edge);
	kosa.excute_kosaraju();
	kosa.print_scc();
}