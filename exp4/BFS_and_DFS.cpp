#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

class Graph
{
public:
    // 构造函数，初始化节点数量
    Graph(int vertices)
    {
        this->vertices = vertices;
        adjList.resize(vertices);
    }

    // 添加边
    void addEdge(int v, int w)
    {
        adjList[v].push_back(w);
        adjList[w].push_back(v); // 无向图
    }

    // 打印图
    void printGraph()
    {
        for (int i = 0; i < vertices; ++i)
        {
            cout << "Vertex " << i << ": ";
            for (int neighbor : adjList[i])
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // 获取邻接表
    const vector<list<int> >& getAdjList() const
    {
        return adjList;
    }

private:
    int vertices;
    vector<list<int> > adjList;
};


using namespace std;

void bfs(const Graph& g, int start)
{
    int vertices = g.getAdjList().size();
    vector<bool> visited(vertices, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        cout << v << " ";

        for (int neighbor : g.getAdjList()[v])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}


using namespace std;

void dfs(const Graph& g, int v, vector<bool>& visited)
{
    visited[v] = true;
    cout << v << " ";

    for (int neighbor : g.getAdjList()[v])
    {
        if (!visited[neighbor])
        {
            dfs(g, neighbor, visited);
        }
    }
}

void dfsWrapper(const Graph& g, int start)
{
    int vertices = g.getAdjList().size();
    vector<bool> visited(vertices, false);
    dfs(g, start, visited);
    cout << endl;
}


int main()
{
    Graph g(5); // 创建一个包含5个节点的图
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(3, 4);

    cout << "BFS Traversal starting from vertex 0: ";
    bfs(g, 0);

    cout << "DFS Traversal starting from vertex 0: ";
    dfsWrapper(g, 0);

    return 0;
}
