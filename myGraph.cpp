#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <cmath>
#include <queue>   // queue, priority queue
#include <utility> // pair
using namespace std;

int timeT = 0; // Timer for DFS.

struct Node
{
    string color;
    int d;  // 1. The shortest distance in BFS; 2. First viewed time in DFS.
    int f;  //                                  1. Time after scanning all it's neighbors.
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
/*----------------------------------------------------------------
                                BFS
                                -> Three status: "WHITE", "GREY" and "BLACK"
                                -> Queue
                                -> O(V + E)
----------------------------------------------------------------*/

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

    queue<int> q; // key point!!!
    q.push(source);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < n; i++) // Breadth-first: Scan all neighbors.
        {
            if (edges[u][i] == 0) // Not connected.
                continue;
            if (nodes[i].color == "WHITE")
            {
                nodes[i].color = "GREY";
                nodes[i].d = nodes[u].d + 1;
                nodes[i].pi = u;
                q.push(i); // Waiting in queue.
            }
        }
        nodes[u].color = "BLACK";
    }
    // for (int i = 0; i < n; i++)
    // {
    //     cout << nodes[i].d << ' ';
    // }
}

/*----------------------------------------------------------------
                                DFS
                                -> Recursive
                                -> O(V + E)
                                -> Depth-first forest
----------------------------------------------------------------*/
void DFS_VISIT(vector<vector<int>> &edges, Node *nodes, int source)
{
    timeT++;
    nodes[source].d = timeT;
    nodes[source].color = "GREY";

    // Traverse neighbors, but depth-first search.
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

// O(V + E)
void DFS(vector<vector<int>> &edges, Node *nodes)
{
    for (int i = 0; i < edges.size(); i++)
    {
        nodes[i].color = "WHITE";
        nodes[i].pi = -1;
    }
    timeT = 0; // Global timer
    for (int i = 0; i < edges.size(); i++)
    {
        // Randomly find source node.
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
                TRANSPORTED_MATRIX[j][i] = 1;
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

// O(V + E)
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
    1. Kruskal
    2. Prim
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

/* DFS, similar to Dijkstra
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
            if(v in Q && w(u, v) < v.key){ // Note: Not relaxation here. We look for the cost connecting to the tree -> w(u, v)/
                v.pi = u;
                v.key = w(u, v);    // Update weights in pq. O(logV).
            }
        }
    }
    return root;
}
*/

/*
    Single Source Shortest Path.
    -> No negative-weighted cycles.
*/

// Initialization
void INITIALIZE_SINGLE_SOURCE(vector<vector<int>> &edges, Node *nodes, int source)
{
    for (int i = 0; i, edges.size(); i++)
    {
        nodes[i].d = INT_MAX;
        node[i].pi = -1;
    }
    node[source] = 0;
}
// Relaxation -> Try to find a shorter path between source and v, using the path from node u.
void RELAX(vector<vector<int>> &edges, Node *nodes, int u, int v)
{
    if (nodes[u].d == INT_MAX)
        return;
    if (nodes[u].d + edges[u][v] < nodes[v].d)
    {
        nodes[v].d = nodes[u].d + edges[u][v];
        nodes[v].pi = u;
    }
}

/*
    Bellman-Ford's Algorithm.
    0. Could handle negative weights.
    1. return a boolean: false if a negative-weighted cycle exists, true if a solution could be found.
*/

/* O(VE)
bool BELLMAN_FORD(vector<vector<int>> &edges, Node *nodes, int soruce){
    INITIALIZE_SINGLE_SOURCE(vector<vector<int>> &edges, Node *nodes, int soruce);
    // Each edge be relaxed |V| - 1 times
    for(int i = 0; i < edges.size() - 1; i++){          // V - 1 times
        for(edge (u,v):G.E) RELAX(edges, nodes, u, v);  // O(E)
    }

    // Check the existence of negative cycles.
    for(edge (u,v):G.E){
        if(u.d + edges[u][v] < v.d) return false;
    }
    return true;
}
*/

// Linear Time -> O(V + E).
DAG_SHORTEST_PATHS(vector<vector<int>> &edges, Node *nodes, int soruce)
{
    TOPOLOGICAL_SORT(edges, nodes);                 // O(V + E)
    INITIALIZE_SINGLE_SOURCE(edges, nodes, soruce); // O(V)

    for (vertex u : G.V) // O(E), in topologically sorted order.
    {
        for (vertex v : u.neighbors)
        {
            RELAX(edges, nodes, u, v);
        }
    }
}

/*
    Dijkstra's Algorithm.
    1. Non-negative weights.
    2. Greedy Algorithm.

*/

void DIJKSTRA(vector<vector<int>> &edges, Node *nodes, int soruce)
{
    INITIALIZE_SINGLE_SOURCE(vector<vector<int>> & edges, Node * nodes, int soruce);
    S = empty set;
    pq = G.V;
    while (!pq.empty())
    { // O(V)
        u = pq.top();
        pq.pop();
        S = S U{U};
        for (vertex v : u.neighbors)
        {
            RELAX(edges, nodes, u, v); // DECREASE_KEY |E| times
        }
    }
}
// Time: O(ElogE), Space: O(V + E)
vector<int> myDijkstra(vector<vector<pair<int, int>>> &graph, int source)
{
    int n = graph.size();
    vector<int> distArr(n, INT_MAX);                                      // memo
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // Store each Vertex as {v.dist, v.id}!
    pq.push({0, source});
    distArr[source] = 0;

    while (!pq.empty()) // O(E)
    {
        pair<int, int> *p = pq.top();
        pq.pop();
        int dist = p->first;
        int u = p->second;

        if (dist > distArr[u])
            continue; // Shorter Path Already Found.

        for (const auto &pair : graph[u])
        {
            int v = pair.first;
            int weight = pair.second;

            // Relaxation
            if (distArr[v] > distArr[u] + weight)
            {
                distArr[v] = distArr[u] + weight;
                pq.push(distArr[v], v); // O(logE)
            }
        }
    }
    return distArr;
}

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