struct Dinic {
    typedef int FT;
    static const FT INF = 1e9, EPS = 1;
    struct FlowEdge {
        int v, u;
        FT cap, flow = 0;
        FlowEdge(int v, int u, FT cap) : v(v), u(u), cap(cap) {}
    };
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0, src, dest;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n) : n(n) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, FT cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < EPS)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[dest] != -1;
    }

    FT dfs(int v, FT pushed) {
        if (pushed <= EPS || v == dest) return pushed;

        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < EPS)
                continue;
            FT tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr < EPS)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }

        return 0;
    }

    FT max_flow(int s, int t) {
        src = s, dest = t;
        FT f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs()) break;
            fill(ptr.begin(), ptr.end(), 0);
            while (FT pushed = dfs(s, INF)) {
                f += pushed;
            }
        }
        return f;
    }
};
