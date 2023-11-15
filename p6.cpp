#include <iostream>
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

    void topologicalSortUtil(int v,bool visited[], stack<int> &Stack) {
        visited[v] = true;

        vector<int>::iterator i;
        for (i = adjList[v].begin(); i != adjList[v].end(); ++i) {
            if (!visited[*i]) {
                topologicalSortUtil(*i, visited, Stack);
            }
        }
        Stack.push(v);
    }

    bool isCyclicUtil(int v, bool visited[], bool recStack[]) {
        visited[v] = true;
        recStack[v] = true;

        vector<int>::iterator i;
        for (i = adjList[v].begin(); i != adjList[v].end(); ++i) {
            if (!visited[*i] && isCyclicUtil(*i, visited, recStack)) {
                return true;
            } else if(recStack[*i]) {
                return true;
            }
        }
        recStack[v] = false;
        return false;
    } 

    bool isCyclic() {
        bool* visited = new bool[v];
        bool* recStack = new bool[v];
        for (int i = 0; i < v; i++) {
            visited[i] = false;
            recStack[i] = false;
        }
        for (int i = 0; i < v; i++) {
            if (!visited[i]) {
                if (isCyclicUtil(i, visited, recStack)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool topologicalSort() {
        if (isCyclic()) {
            return false;
        }
        bool* visited = new bool[v];

        for (int i = 0; i < v; i++) {
            visited[i] = false;
        }

        stack<int> Stack;
        for (int i = 0; i < v; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, Stack);
            }
        }

        for (int i = 0; i < v; i++) {
            cout << Stack.top() + 1 << " ";
            Stack.pop();
        }
        return true;

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
    if (!g.topologicalSort()) {
        cout << "-1";
    }
    cout << endl;
}