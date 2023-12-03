#include <iostream>
using namespace std;

#define edge pair<int, int>

class Graph{
public:
    vector<pair<int, edge> > G;
    int v;

    Graph(int v) {
        this->v  = v;
        G.clear();
    }

    void add_edge(int node1, int node2, int w) {
        G.push_back(make_pair(w, edge(node1 - 1, node2 - 1)));
    }

    int kruskal() {
        vector<int> tree_id(v);
        for (int i = 0; i < v; i++) {
            tree_id[i] = i;
        }
        sort(G.begin(), G.end());
        int cost = 0;
        for (int i = 0; i < v; i++) {
            if (tree_id[G[i].second.first] != tree_id[G[i].second.second]) {
                cost += G[i].first;
                int old_id = tree_id[G[i].second.first], new_id = tree_id[G[i].second.second];
                for (int j = 0; j < v; j++) {
                    if (tree_id[j] == old_id) {
                        tree_id[j] = new_id;
                    }
                }
            }
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
    cout << g.kruskal() << endl;

}