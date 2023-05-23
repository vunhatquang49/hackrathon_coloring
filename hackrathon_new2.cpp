#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <time.h>
#include <fstream>
using namespace std;

int saturation_degree(int node, const vector<int>& color, const vector<vector<int>>& adj, const vector<int>& saturation) {
    return saturation[node];
}

vector<int> DSatTur(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> color(n, -1);
    vector<int> saturation(n, 0);
    vector<int> uncolored_nodes(n);
    for (int i = 0; i < n; i++) {
        uncolored_nodes[i] = i;
    }

    color[0] = 0;
    int max_color = 0;
    uncolored_nodes.erase(uncolored_nodes.begin());

    while (!uncolored_nodes.empty()) {
        int max_saturation = -1;
        int chosen_node = -1;
        int chosen_index = -1;

        for (int i = 0; i < uncolored_nodes.size(); i++) {
            int node = uncolored_nodes[i];
            int sat = saturation_degree(node, color, adj, saturation);
            if (sat > max_saturation) {
                max_saturation = sat;
                chosen_node = node;
                chosen_index = i;
            }
        }

        uncolored_nodes.erase(uncolored_nodes.begin() + chosen_index);

        unordered_set<int> used_colors;
        for (auto v : adj[chosen_node]) {
            if (color[v] != -1) {
                used_colors.insert(color[v]);
            } else {
                saturation[v]++;
            }
        }

        int j = 0;
        while (used_colors.find(j) != used_colors.end()) {
            j++;
        }
        color[chosen_node] = j;
        max_color = max(max_color, j);
    }

    return color;
}
int main()
{
    ofstream output_file("output_hackrathon.txt");
    ifstream input_file("input.txt");
    int n, m;
    input_file >> n >> m;
            clock_t start_time = clock();

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        input_file >> u >> v;
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }

    vector<int> color = DSatTur(adj);
    int max_color = *max_element(color.begin(), color.end());

    output_file << max_color + 1 << endl;
    for (int i = 0; i < n; i++)
    {
        output_file << color[i] + 1 << endl;
    }
    input_file.close();
    output_file.close();
    clock_t end_time = clock();
    double elapsed_time = double(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.2f seconds\n", elapsed_time);
    system(".\\check_valid_coloring input.txt output_hackrathon.txt");
    return 0;
}