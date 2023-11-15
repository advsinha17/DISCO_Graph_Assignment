#include <iostream>
#include <queue>
using namespace std;


class Graph {
public:
    vector<vector<int> > adjList;
    vector<int> color;
    int v;

    Graph(int v) {
        this->v = v;
        adjList.resize(v);
        color.resize(v);
        for (int i = 0; i < v; i++) {
            color[i] = -1;
        }
    }

    void add_edge(int node1, int node2) {
        adjList[node1 - 1].push_back(node2 - 1);
        adjList[node2 - 1].push_back(node1 - 1);
    }

    bool isBipartite() {
        for (int i = 0; i < v; i++) {
            if (color[i] == -1) {
                if (!bipartiteCheck(i)) {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool bipartiteCheck(int s) {
        queue<int> q;
        q.push(s);
        color[s] = 0;

        while(!q.empty()) {
            int node = q.front(); 
            q.pop();
            vector<int>::iterator i;
            for (i = adjList[node].begin(); i != adjList[node].end(); ++i) {
                if (color[*i] == -1) {
                    color[*i] = 1 - color[node];
                    q.push(*i);
                } else if(color[*i] == color[node]) {
                    return false;
                }
            }
        }
        return true;
    }
};


int main() {
    int n, m;
    cin >> n >> m;
    Graph g(n);
    int k, l;
    for (int i = 0; i < m; i++) {
        cin >> k >> l;
        g.add_edge(k, l);
    }
    g.isBipartite() ? cout <<  "YES\n" : cout << "NO\n";
}