#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <fstream>
using namespace std;

vector<vector<int>> find_independent_sets(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<vector<int>> independent_sets;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            vector<int> independent_set;
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                int node = q.front();
                q.pop();
                independent_set.push_back(node);

                for (auto neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        for (auto next : adj[neighbor]) {
                            if (!visited[next]) {
                                q.push(next);
                                visited[next] = true;
                            }
                        }
                    }
                }
            }

            independent_sets.push_back(independent_set);
        }
    }

    return independent_sets;
}

vector<int> greedy_independent_set_coloring(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> color(n, -1);
    vector<vector<int>> independent_sets = find_independent_sets(adj);

    int current_color = 0;
    for (const auto& independent_set : independent_sets) {
        for (int node : independent_set) {
            color[node] = current_color;
        }
        current_color++;
    }

    return color;
}

int main() {
    ifstream input_file("input.txt");
    ofstream output_file("output_hackrathon.txt");

    int n, m;
    input_file >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        input_file >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    vector<int> color = greedy_independent_set_coloring(adj);
    int max_color = *max_element(color.begin(), color.end());

    output_file << max_color + 1 << endl;
    for (int i = 0; i < n; i++) {
        output_file << color[i] + 1 << endl;
    }

    input_file.close();
    output_file.close();
    system(".\\check_valid_coloring input.txt output_hackrathon.txt");
    return 0;
}