#include <iostream>
#include <vector>

using namespace std;

bool is_safe(int v, const vector<vector<int>>& adj, const vector<int>& color, int c) {
    for (int u : adj[v]) {
        if (color[u] == c) {
            return false;
        }
    }
    return true;
}

bool graph_coloring_util(const vector<vector<int>>& adj, vector<int>& color, int v, int m) {
    int n = adj.size();
    if (v == n) {
        return true;
    }

    for (int c = 1; c <= m; c++) {
        if (is_safe(v, adj, color, c)) {
            color[v] = c;
            if (graph_coloring_util(adj, color, v + 1, m)) {
                return true;
            }
            color[v] = 0;
        }
    }

    return false;
}

void graph_coloring(const vector<vector<int>>& adj, int m) {
    int n = adj.size();
    vector<int> color(n, 0);

    if (graph_coloring_util(adj, color, 0, m)) {
        for (int i = 0; i < n; i++) {
            cout << color[i] << endl;
        }
    } else {
        cout << "No solution" << endl;
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    graph_coloring(adj, k);

    return 0;
}