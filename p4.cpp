#include <iostream>
#include <queue>
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
        adjList[node2 - 1].push_back(node1 - 1);
    }

    int findShortestPath(int start, int end) {
        queue<int> q;
        bool* visited = new bool[v];
        int* distance = new int[v];
        for (int i = 0; i < v; i++) {
            visited[i] = false;
            distance[i] = -1;
        }

        q.push(start);
        visited[start] = true;
        distance[start] = 0;

        while(!q.empty()) {
            int node = q.front();
            q.pop();

            vector<int>::iterator i;
            for (i = adjList[node].begin(); i != adjList[node].end(); ++i) {
                if (!visited[*i]) {
                    visited[*i] = true;
                    distance[*i] = distance[node] + 1;
                    q.push(*i);

                    if (*i == end) {
                        return distance[*i];
                    }
                }
            } 
        }
        return -1;
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
    cout << g.findShortestPath(0, n - 1) << endl;
}