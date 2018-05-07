#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <list>

using namespace std;

class TopologicalSort {
public:
	TopologicalSort(vector<pair<string, string>> edge) {
		for (auto it = edge.begin(); it != edge.end(); it++) {
			node.insert(it->first);
			node.insert(it->second);
			adj.insert({ it->first, it->second });
		}
		node_num = node.size();
	}

	void execute() {
		for_each(node.begin(), node.end(), [this](string n) {visited[n] = false; });
		for_each(node.begin(), node.end(), [this](string n) {if (!visited[n]) dfs(n); });
	}

	void print_topological_list() {
		for_each(topological_list.begin(), topological_list.end(),
			[](string n) {cout << n << endl; });
	}

private:
	int node_num;
	unordered_multimap<string, string> adj;
	unordered_set<string> node;
	unordered_map<string, bool> visited;
	list<string> topological_list;

	void dfs(string n) {
		visited[n] = true;
		for (auto pos = adj.equal_range(n); pos.first != pos.second; pos.first++)
			if (!visited[pos.first->second])
				dfs(pos.first->second);
		topological_list.push_front(n);
	}
};

int main() {
	vector<pair<string, string>> edge{ {"shirt", "tie"}, {"shirt", "belt"}, {"tie", "jacket"},
									   {"belt", "jacket"}, {"pants", "belt"}, {"pants", "shoes"},
									   {"undershorts", "pants"}, {"undershorts", "shoes"},
									   {"socks", "shoes"}, {"watch", "watch"} };
	TopologicalSort topological(edge);
	topological.execute();
	topological.print_topological_list();
}
