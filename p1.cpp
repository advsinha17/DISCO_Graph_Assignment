#include <iostream>
using namespace std;

int graphPossible(vector<int> &v) {

    while (1) {
        sort(v.begin(), v.end(), greater<int>());

        bool zeros = true;
        for (int i = 0; i < v.size(); i++) {
            if (v[i] != 0) {
                zeros = false;
                break;
            }
        }

        if (zeros) {
            return 1;
        }

        int first = v[0];
        v.erase(v.begin());

        if (first > v.size()) {
            return 0;
        }

        for (int i = 0; i < first; i++) {
            v[i]--;
            if (v[i] < 0) {
                return 0;
            }
        }
    }
}



int main() {
    int n;
    cin >> n;
    vector<int> v;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        v.push_back(k);
    }

    graphPossible(v) ? cout << "YES\n" : cout << "NO\n";

}