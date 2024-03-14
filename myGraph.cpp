#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <cmath>
#include <queue>   // queue, priority queue
#include <utility> // pair
using namespace std;

int timeT = 0;

struct Node
{
    string color;
    int d;  // the shortest distance in BFS; First viewed time in DFS.
    int f;  //                               Time after scan all it's neighbor.
    int pi; // Previous Node
};

void PRINT_PATH(Node *nodes, int source, int des)
{
    while (source != des)
    {
        if (nodes[des].pi == -1)
        {
            cout << "No path.";
            return;
        }
        cout << des << " -> ";
        des = nodes[des].pi;
    }
    cout << '1' << endl;
}
void BFS(vector<vector<int>> &edges, Node *nodes, int source)
{
    int n = edges.size();
    for (int i = 0; i < n; i++)
    {
        nodes[i].color = "WHITE";
        nodes[i].d = INT_MAX;
        nodes[i].pi = -1;
    }
    nodes[source].color = "GREY";
    nodes[source].d = 0;
    nodes[source].pi = -1;

    queue<int> q;
    q.push(source);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < n; i++)
        {
            // if(i == u) continue;
            if (edges[u][i] == 0)
                continue;
            if (nodes[i].color == "WHITE")
            {
                nodes[i].color = "GREY";
                nodes[i].d = nodes[u].d + 1;
                nodes[i].pi = u;
                q.push(i);
            }
        }
        nodes[u].color = "BLACK";
    }
    // for (int i = 0; i < n; i++)
    // {
    //     cout << nodes[i].d << ' ';
    // }
}

void DFS_VISIT(vector<vector<int>> &edges, Node *nodes, int source)
{
    timeT++;
    nodes[source].d = timeT;
    nodes[source].color = "GREY";
    for (int v = 0; v < edges.size(); v++)
    {
        if (edges[source][v] == 0)
            continue;
        if (nodes[v].color == "WHITE")
        {
            nodes[v].pi = source;
            DFS_VISIT(edges, nodes, v);
        }
    }
    nodes[source].color = "BLACK";
    timeT++;
    nodes[source].f = timeT;
    // Topological sort: Push it onto the front of a linked list.
}

void DFS(vector<vector<int>> &edges, Node *nodes)
{
    for (int i = 0; i < edges.size(); i++)
    {
        nodes[i].color = "WHITE";
        nodes[i].pi = -1;
    }
    timeT = 0;
    for (int i = 0; i < edges.size(); i++)
    {
        if (nodes[i].color == "WHITE")
            DFS_VISIT(edges, nodes, i);
    }
}

vector<vector<int>> MATRIX_TRANSPORT(vector<vector<int>> &edges)
{
    vector<vector<int>> TRANSPORTED_MATRIX(edges[0].size(), vector<int>(edges.size()));
    for (int i = 0; i < edges.size(); i++)
    {
        for (int j = 0; j < edges.size(); j++)
        {
            if (edges[i][j] == 1)
                transaction_safe_dynamic[j][i] = 1;
        }
    }
    return TRANSPORTED_MATRIX;
}

bool nodeComparator(const Node &n1, const Node &n2)
{
    return n1.f > n2.f;
}

void DFS_TRANSPORT(vector<vector<int>> &edges, Node *nodes)
{
    vector<vector<int>> TRANSPORTED_MATRIX = MATRIX_TRANSPORT(edges);
    for (int i = 0; i < TRANSPORTED_MATRIX.size(); i++)
    {
        nodes[i].color = "WHITE";
        nodes[i].pi = -1;
    }
    timeT = 0;
    // Considering the vertices in order of decreasing node.f
    vector<Node> nodeVec;
    for (int i = 0; i < edges.size(); i++)
    {
        nodeVec.push_back(nodes[i]);
    }
    sort(nodeVec.begin(), nodeVec.end(), nodeComparator());
    for (int i = 0; i < nodeVec.size(); i++)
    {
        if (nodeVec[i].color == "WHITE")
            DFS_VISIT(TRANSPORTED_MATRIX, nodes, i);
    }
}

void PRINT_DFS(vector<vector<int>> &edges, Node *nodes)
{
    for (int i = 0; i < edges.size(); i++)
    {
        printf("Node [%d]: %d/%d \n", i, nodes[i].d, nodes[i].f);
    }
}

LinkedListNode *TOPOLOGICAL_SORT(vector<vector<int>> &edges, Node *nodes)
{
    DFS(edges, nodes);
    LinkedListNode *head;
    // When a node becomes BLACK in DFS, insert it onto the front of a linked list.
    // return head;
}

void STRONGLY_CONNECTED_COMPONENTS(vector<vector<int>> &edges, Node *nodes)
{
    DFS(edges, nodes);
    DFS_TRANSPORT(edges, nodes);
}

/*
    Minimum Spanning Tree (MST)
*/

/*
GENERIC_MST(G, w){
    A = an empty set;
    while(A does not form a spanning tree){ // run (V - 1) times
        find an edge(u, v) that is safe for A;
        A = A U (u, v);
    }
}
*/

/*
MST_KRUSKAL(G, w){                  // O(ElogV)
    A = an empty set;
    for(vertex v:V){
        MAKE_SET(v);                // Every vertex starts as a set.
    }
    sort(E);                        // ElogE -> ElogV if E << V^2
    for(edge (u, v):E){             // Now it's in nondecreasing order.
        if(FIND_SET(u) != FIND_SET(v)){
            A = A U e
            UNION(u, v);
        }
    }
    return A;
}
*/

/*
MST_PRIM(G, w, root){               // O(ElogV)
    A = an empty set;
    for(vertex v:V){
        v.key = INT_MAX;            // weight to prev vertex
        v.pi = null;                // prev vertex
    }
    root.key = 0;
    Q = G.V                         // priority Queue (min-heap) -> O(V)
    while(!Q.empty()){              // run V times
        u = EXTRACT_MIN(Q);         // O(logV)
        A = A U (u.pi, u);          // Find an edge to put in A.
        for each v in u.neighbors{  // run O(2E) times in total
            if(v in Q && w(u, v) < v.key){
                v.pi = u;
                v.key = w(u, v);    // O(logV)
            }
        }
    }
    return root;
}
*/

int main()
{
    Node *nodes = new Node[8];
    vector<vector<int>> edges(8, vector<int>(8, 0));
    edges[0][1] = edges[0][4] = edges[1][0] = edges[1][5] = edges[2][3] = edges[2][5] = edges[2][6] = 1;
    edges[3][2] = edges[3][6] = edges[3][7] = edges[4][0] = edges[5][1] = edges[5][2] = edges[5][6] = 1;
    edges[6][2] = edges[6][3] = edges[6][5] = edges[6][7] = edges[7][3] = edges[7][6] = 1;

    // BFS(edges, nodes, 1);
    // for (int i = 0; i < edges.size(); i++)
    // {
    //     PRINT_PATH(nodes, 1, i);
    // }

    DFS(edges, nodes);
    PRINT_DFS(edges, nodes);
    return 0;
}

// Exercise 22.3-1
//   W G B
// W 0 0 0
// G 1 1 1
// B 0 0 0