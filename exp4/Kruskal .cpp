#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class UnionFind
{
public:
    UnionFind(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int u)
    {
        if (parent[u] != u)
        {
            parent[u] = find(parent[u]); // Â·¾¶Ñ¹Ëõ
        }
        return parent[u];
    }

    void unionSets(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV)
        {
            if (rank[rootU] > rank[rootV])
            {
                parent[rootV] = rootU;
            }
            else if (rank[rootU] < rank[rootV])
            {
                parent[rootU] = rootV;
            }
            else
            {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

private:
    vector<int> parent, rank;
};

struct Edge
{
    int u, v, weight;
    bool operator<(const Edge& e) const
    {
        return weight < e.weight;
    }
};

class KruskalGraph
{
public:
    KruskalGraph(int vertices)
    {
        this->vertices = vertices;
    }

    void addEdge(int u, int v, int weight)
    {
        edges.push_back({u, v, weight});
    }

    void kruskal()
    {
        sort(edges.begin(), edges.end());

        UnionFind uf(vertices);
        vector<Edge> mst;

        for (const Edge& e : edges)
        {
            int u = e.u, v = e.v;

            if (uf.find(u) != uf.find(v))
            {
                uf.unionSets(u, v);
                mst.push_back(e);
            }
        }

        cout << "Edges in the Minimum Spanning Tree:" << endl;
        for (const Edge& e : mst)
        {
            cout << e.u << " - " << e.v << " with weight " << e.weight << endl;
        }
    }

private:
    int vertices;
    vector<Edge> edges;
};

int main()
{
    
    // Kruskal Test
    KruskalGraph kg(4);
    kg.addEdge(0, 1, 10);
    kg.addEdge(0, 2, 6);
    kg.addEdge(0, 3, 5);
    kg.addEdge(1, 3, 15);
    kg.addEdge(2, 3, 4);

    cout << "Kruskal Algorithm (Minimum Spanning Tree):" << endl;
    kg.kruskal();

    return 0;
}
