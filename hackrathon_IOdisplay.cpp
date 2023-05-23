#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <time.h>
#include <fstream>
using namespace std;
int main()
{
    int n, m;
    cin>> n >> m;
    
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }
    vector<int> color(n, -1);
    color[0] = 0;
    int max_color = 0;
    for (int i = 1; i < n; i++)
    {
        set<int> used_colors;
        for (auto v : adj[i])
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
    cout << max_color + 1 << endl;
    for (int i = 0; i < n; i++)
    {
        cout << color[i] + 1 << endl;
    }
    
    return 0;
}