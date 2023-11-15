#include <iostream>
#include <stack>
using namespace std;

class Graph {
public:
    vector<vector<int> > adjList;
    int v;
    vector<int> parent;
    int cycle_start, cycle_end;

    Graph(int v) {
        this->v = v;
        adjList.resize(v);
        parent.resize(v);
        cycle_start = -1;
        cycle_end = -1;
    }

    void add_edge(int node1, int node2) {
        adjList[node1 - 1].push_back(node2 - 1);
        adjList[node2 - 1].push_back(node1 - 1);
    }

    bool dfs(int v, int par, bool visited[]) {
        visited[v] = true;
        vector<int>::iterator i;
        for (i = adjList[v].begin(); i != adjList[v].end(); ++i) {
            if (*i == par) continue;
            if (visited[*i]) {
                cycle_end = v;
                cycle_start = *i;
                return true;
            }
            parent[*i] = v;
            if (dfs(*i, parent[*i], visited)) {
                return true;
            }
        }
        return false;
    }

    void isCyclic() {
        bool* visited = new bool[v];
        for (int i = 0; i < v; i++) {
            visited[i] = false;
            parent[i] = -1;
        }

        for (int i = 0; i < v; i++) {
            if (!visited[i] && dfs(i, parent[i], visited)) {
                break;
            }
        }

        if (cycle_start == -1) {
            cout << "-1\n";
            return;
        }
        vector <int> cycle;
        cycle.push_back(cycle_start);
        for (int i = cycle_end; i != cycle_start; i = parent[i]) {
            cycle.push_back(i);
        }
        vector<int>::iterator i;
        for (i = cycle.begin(); i != cycle.end(); i++) {
            cout << *i + 1 << " ";
        }
        cout << endl;
    }


};

int main() {
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int k, l;
        cin >> k >> l;
        g.add_edge(k, l);
    }
    g.isCyclic();
}