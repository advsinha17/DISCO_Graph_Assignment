#include <iostream>
using namespace std;

class Graph {
public:
    vector<vector<pair<int, int> > > adjList;
    int v;

    Graph(int v) {
        this->v = v;
        adjList.resize(v);
    }

    void add_edge(int node1, int node2, int weight) {
        adjList[node1 - 1].push_back(make_pair(node2 - 1, weight));
        adjList[node2 - 1].push_back(make_pair(node1 - 1, weight));
    }

    int selectMinVertex(vector<bool> &setMST) {
        int minCost = INT_MAX;
        int minVertex = -1;
        for (int i = 0; i < v; i++) {
            if (setMST[i]) {
                vector<pair<int, int> >::iterator it;
                for (it = adjList[i].begin(); it != adjList[i].end(); ++it) {
                    if (!setMST[it->first]) {
                        if (it->second < minCost) {
                            minCost = it->second;
                            minVertex = it->first;
                        }
                    }
                }
            }
        }
        setMST[minVertex] = true;
        return minCost;
    }

    int mstCost() {
        vector<bool> setMST;
        for (int i = 0; i < v; i++) {
            setMST.push_back(false);
        }
        
        int cost = 0;
        setMST[0] = true;
        for (int i = 0; i < v - 1; i++) {
            cost += selectMinVertex(setMST);
        }
        return cost;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int k, l, w;
        cin >> k >> l >> w;
        g.add_edge(k, l, w);
    }
    cout << g.mstCost() << endl;

}