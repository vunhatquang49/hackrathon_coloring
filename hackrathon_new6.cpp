#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <time.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

int saturation_degree(int node, const vector<int>& color, const vector<vector<int>>& adj, const vector<int>& freq) {
    int saturation = 0;
    for (auto neighbor : adj[node]) {
        if (color[neighbor] != -1) {
            saturation += freq[color[neighbor]];
        }
    }
    return saturation;
}

vector<int> DSatTur(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> color(n, -1);
    color[0] = 0;
    int max_color = 0;

    vector<int> freq(n, 0);
    for (auto neighbors : adj) {
        for (auto neighbor : neighbors) {
            freq[color[neighbor]]++;
        }
    }

    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            int saturation = saturation_degree(i, color, adj, freq);
            pq.push({saturation, i});
        }
    }

    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();

        set<int> used_colors;
        for (auto v : adj[node]) {
            if (color[v] != -1) {
                used_colors.insert(color[v]);
            }
        }

        int j = 0;
        while (used_colors.find(j) != used_colors.end()) {
            j++;
        }
        color[node] = j;
        max_color = max(max_color, j);

        for (auto neighbor : adj[node]) {
            if (color[neighbor] == -1) {
                freq[color[node]]++;
                pq.push({saturation_degree(neighbor, color, adj, freq), neighbor});
            }
        }
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