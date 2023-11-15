#include <iostream>
#include <queue>
using namespace std;

class HasseDiagram {
public:
    vector<vector<int> > adjList;
    int v;

    HasseDiagram(int v) {
        this->v = v;
        adjList.resize(v);
    }

    void add_edge(int node1, int node2) {
        adjList[node1 - 1].push_back(node2 - 1);
    }

    bool isReachable(int s, int d) {
        if (s == d) {
            return true;
        }

        queue<int> q;
        q.push(s);
        bool* visited = new bool(v);
        for (int i = 0; i < v; i++) {
            visited[i] = false;
        }
        visited[s] = true;

        while(!q.empty()) {
            int node = q.front();
            q.pop();
            vector<int>::iterator i;
            for (i = adjList[node].begin(); i != adjList[node].end(); ++i) {
                if (*i == d) {
                    return true;
                }

                if (!visited[*i]) {
                    visited[*i] = true;
                    q.push(*i);
                }
            }

        }
        return false;
    }
};

int glb(HasseDiagram &o, int x, int y) {

    vector<int> x_reachable, y_reachable;
    for (int i = 0; i < o.v; i++) {
        if(o.isReachable(i, x)) {
            x_reachable.push_back(i);
        } 
        if (o.isReachable(i, y)) {
            y_reachable.push_back(i);
        }
    }

    vector<int> intersection(min(x_reachable.size(), y_reachable.size()));

    vector<int>::iterator it = set_intersection(x_reachable.begin(), x_reachable.end(),
    y_reachable.begin(), y_reachable.end(), intersection.begin());
    intersection.resize(it - intersection.begin());

    if (intersection.empty()) {
        return -1;
    }

    for (int i = 0; i < intersection.size(); i++) {
        bool flag = true;
        for (int j = 0; j < intersection.size(); j++) {
            if (!o.isReachable(intersection[j], intersection[i])) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return intersection[i] + 1;
        }
    }
    return -1;
}

int main() {
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    HasseDiagram h(n);
    HasseDiagram h_rev(n);
    for (int i = 0; i < m; i++) {
        int k, l;
        cin >> k >> l;
        h.add_edge(k, l);
        h_rev.add_edge(l, k);
    }
    cout << glb(h, x - 1, y - 1) << " " << glb(h_rev, x - 1, y - 1) << endl;
}