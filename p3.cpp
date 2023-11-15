#include <iostream>
using namespace std;

class Graph {
public:
    vector<vector<int> > adjList;
    int v;

    Graph(int v) {
        this->v = v;
        adjList.resize(v);
    }

    void add_edge(int node1, int node2) {
        adjList[node1 - 1].push_back(node2 - 1);
    }

    vector<int> findSimplePath(int s, int d) {
        vector<int> path;
        vector<int> result;

        bool* visited = new bool[v];
        for (int i = 0; i < v; i++) {
            visited[i] = false;
        }
        shortestPathUtil(s, d, visited, path, result);
        return result;
    }

    void shortestPathUtil(int s, int d, bool visited[], vector<int>& path, vector<int>& result) {
        visited[s] = true;
        path.push_back(s);

        if (s == d) {
            result = path;
        } else {
            vector<int>::iterator i;
            for (i = adjList[s].begin(); i != adjList[s].end(); ++i) {
                if (!visited[*i]) {
                    shortestPathUtil(*i, d, visited, path, result);
                    if (!result.empty()) break;
                }
            }
        }
        path.pop_back();
        visited[s] = false;
    }
};

int main() {
    int n;
    cin >> n;
    Graph g(n);
    for (int i = 0; i < n - 1; ++i) {
        int k, l;
        cin >> k >> l;
        g.add_edge(k, l);
        g.add_edge(l, k);
    }
    int s, d;
    cin >> s >> d;
    vector<int> result = g.findSimplePath(s - 1, d - 1);
    cout << result.size() << endl;
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] + 1 << " ";
    }
    cout << endl;
}