#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <time.h>
#include <fstream>
using namespace std;

vector<int> sort_nodes_by_degree(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<pair<int, int>> node_degrees(n);
    for (int i = 0; i < n; i++) {
        node_degrees[i] = {adj[i].size(), i};
    }
    sort(node_degrees.rbegin(), node_degrees.rend());
    vector<int> sorted_nodes(n);
    for (int i = 0; i < n; i++) {
        sorted_nodes[i] = node_degrees[i].second;
    }
    return sorted_nodes;
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
    vector<int> sorted_nodes = sort_nodes_by_degree(adj);
    vector<int> color(n, -1);
    color[sorted_nodes[0]] = 0;
    int max_color = 0;
    for (int i = 1; i < n; i++)
    {
        set<int> used_colors;
        for (auto v : adj[sorted_nodes[i]])
        {
            if (color[v] != -1)
            {
                used_colors.insert(color[v]);
            }
        }
        int j = 0;
        while (used_colors.find(j) != used_colors.end())
        {
            j++;
        }
        color[i] = j;
        max_color = max(max_color, j);
    }
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