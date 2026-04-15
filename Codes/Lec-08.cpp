#include <bits/stdc++.h>
using namespace std;

struct TwoSAT {
    int n;
    vector<vector<int>> g, rg ; // implication graph + reverse (2n nodes each )
    vector<int> finish_order;
    vector<int> comp ; // comp [v] = SCC id of node v
    vector<bool> visited ;
    TwoSAT (int n) : n(n), g(2 * n), rg(2 * n), comp(2 * n), visited(2 * n) {}
    // Add directed edge u - > v and maintain its reverse for Kosaraju pass 2
    void add_edge (int u, int v) {
        g[u].push_back (v);
        rg[v].push_back(u);
    }
    // Clause : ( x_i = f ) OR ( x_j = h )
    // node i = " x_i is true " | node i + n = " x_i is false "
    // f = true -> positive literal ( x_i )
    // f = false -> negative literal ( not x_i )
    void add_clause (int i, bool f, int j, bool h) {
        add_edge(i + (f ? n : 0), j + (h ? 0 : n)); // neg ( xi = f ) -> ( xj = h )
        add_edge(j + (h ? n : 0), i + (f ? 0 : n )); // neg ( xj = h ) -> ( xi = f )
    }

    void dfs1(int v) {          // identical to Kosaraju pass 1
        visited[v] = true;
        for (int u : g[v]) if (!visited[u]) dfs1(u);
        finish_order.push_back(v);
    }

    void dfs2(int v, int id) { // identical to Kosaraju pass 2
        visited[v] = true;
        comp[v] = id;
        for (int u : rg[v]) if (!visited[u]) dfs2(u, id);
    }

    // Returns true iff satisfiable; answer[i] holds the assigned value of x_i
    bool solve(vector<int>& answer) {
        fill(begin(visited), end(visited), false);
        for (int i = 0; i < 2 * n; i++) {
            if (!visited[i]) dfs1(i);  // Kosaraju pass 1
        }

        fill(begin(visited), end(visited), false);
        reverse(begin(finish_order), end(finish_order));
        int id = 0;
        for (int v : finish_order) {
            if (!visited[v]) dfs2(v, id++); // Kosaraju pass 2

        }

        answer.resize(n);
        for (int i = 0; i < n; i++) {
            if (comp[i] == comp[i + n]) return false; // contradiction
            answer[i] = (comp[i] > comp[i + n]);      // later SCC = chosen value
        }
        return true;
    }
};
