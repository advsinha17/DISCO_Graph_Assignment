#include <iostream>
using namespace std;

class Graph
{
public:
    vector<vector<int> > adjList;    
    int v;

    Graph(int v) {
        this->v = v;
        adjList.resize(v);
    }

    void add_edge(int node1, int node2) {
        adjList[node1 - 1].push_back(node2 - 1);
        adjList[node2 - 2].push_back(node1 - 1);
    }

    int connectedComponents() {
        bool* visited = new bool[v];
        int count = 0;

        for (int i = 0; i < v; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < v; i++){
            if (!visited[i]) {
                bfsUtil(i, visited);
                count++;

            }
        }
        return count;
    }

    void bfsUtil(int v, bool visited[]) {
        visited[v] = true;

        vector<int>::iterator i;
        for (i = adjList[v].begin(); i != adjList[v].end(); i++) {
            if (!visited[*i]) {
                bfsUtil(*i, visited);
            }
        }
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

    cout << g.connectedComponents() << endl;
}