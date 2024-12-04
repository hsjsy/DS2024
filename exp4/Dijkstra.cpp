#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class WeightedGraph
{
public:
    WeightedGraph(int vertices)
    {
        this->vertices = vertices;
        adjList.resize(vertices);
    }

    void addEdge(int u, int v, int weight)
    {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // 无向图
    }

    void dijkstra(int start)
    {
        vector<int> dist(vertices, INT_MAX);
        dist[start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        pq.push({0, start});

        while (!pq.empty())
        {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto& neighbor : adjList[u])
            {
                int v = neighbor.first;       // 邻接点
                int weight = neighbor.second; // 边的权重

                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        for (int i = 0; i < vertices; ++i)
        {
            cout << "Distance from " << start << " to " << i << " is: " << dist[i] << endl;
        }
    }

private:
    int vertices;
    vector<vector<pair<int, int> > > adjList; // 存储邻接表，pair 存储邻接点和边的权重
};

int main()
{
    // Dijkstra Test
    WeightedGraph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 9);
    g.addEdge(3, 4, 4);

    cout << "Dijkstra Algorithm (Starting from Vertex 0):" << endl;
    g.dijkstra(0);

    return 0;
}
