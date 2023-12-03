#include <iostream>
#include <vector>
#include <stack>
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

    bool topologicalSortUtil(int v, bool visited[], stack<int>& Stack, bool recStack[]) {
        visited[v] = true;
        recStack[v] = true;

        vector<int>::iterator i;
        for (i = adjList[v].begin(); i != adjList[v].end(); ++i) {
            if (!visited[*i] && !topologicalSortUtil(*i, visited, Stack, recStack)) {
                return false;
            } if (recStack[*i]) {
                return false;
            }
        }
        Stack.push(v);
        recStack[v] = false;
        return true;
    }


    void topologicalSort() {
        stack<int> Stack;

        bool* visited = new bool[v];
        bool* recStack = new bool[v];
        for (int i = 0; i < v; i++) {
            visited[i] = false;
            recStack[i] = false;
        }

        bool flag = true;

        for (int i = 0; i < v; i++) {
            if (!visited[i]) {
                if (!topologicalSortUtil(i, visited, Stack, recStack)) {
                    flag = false;
                    break;
                }
            }
        }

        if (!flag) {
            cout << "-1\n";
            return;
        }

        while(!Stack.empty()) {
            cout << Stack.top() + 1 << " ";
            Stack.pop();
        }
        cout << endl;

    }
};

int main() {

    int v;
    cin >> v;
    Graph g(v);
    int k, m;
    for (int i = 0; i < v; i++) {
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> m;
            g.add_edge(m, i + 1);
        }
    }
    g.topologicalSort();
}