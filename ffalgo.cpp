// C++ program for implementation of Ford Fulkerson algorithm
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <fstream>
#include <algorithm>
using namespace std;

struct Matrix {
	int sz;
	int** m;
};

typedef struct Matrix Matrix;

int fordFulkerson(int **, int, int);

Matrix * Matrix_init(int sz) {
  int ** m;
  struct Matrix* matrix = new Matrix;
  matrix->sz = sz;
  m = new int*[sz];
  for (size_t i = 0; i < sz; i++) {
    m[i] = new int[sz];
  }
  matrix->m = m;
  return matrix;
}

Matrix * Matrix_read(string fname) {
  ifstream c(fname.c_str());
  ifstream f(fname.c_str());
  struct Matrix* matrix = new Matrix;
  if(!f) return NULL;
  int sz = count(istreambuf_iterator<char>(c),istreambuf_iterator<char>(), '\n');
  matrix = Matrix_init(sz);
  for (size_t y = 0; y < sz; y++) {
    for (size_t x = 0; x < sz; x++) {
      f >> matrix->m[y][x];
      //std::cout << matrix->m[y][x] << ' ';
    }
    //std::cout << '\n';
  }
  return matrix;
}

void Matrix_print(Matrix *m) {
  for (size_t x = 0; x < m->sz; x++) {
    for (size_t y = 0; y < m->sz; y++) {
      std::cout << m->m[x][y] << ' ';
    }
    std::cout << '\n';
  }
}

int Matrix_fordFulkerson(Matrix *m) {
  return fordFulkerson(m->m, 0, (m->sz)-1);
}

// Number of vertices in given graph
#define V 6

/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not visited
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v=0; v<V; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}

// Returns the maximum flow from s to t in the given graph
//int fordFulkerson(int graph[V][V], int s, int t)
int fordFulkerson(int **graph, int s, int t)
{
    int u, v;

    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    int rGraph[V][V]; // Residual graph where rGraph[i][j] indicates
                     // residual capacity of edge from i to j (if there
                     // is an edge. If rGraph[i][j] is 0, then there is not)
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];

    int parent[V];  // This array is filled by BFS and to store path

    int max_flow = 0;  // There is no flow initially

    // Augment the flow while tere is path from source to sink
    while (bfs(rGraph, s, t, parent))
    {
        // Find minimum residual capacity of the edges along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // update residual capacities of the edges and reverse edges
        // along the path
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    // Return the overall flow
    return max_flow;
}

int** testLoad() {
  int **g = new int * [16];
  int graph[18][18];
  ifstream in("graph.txt");

  if(!in) std::cout << "File open failed !" << '\n';
  else {
    for (size_t y = 0; y < 6; y++) {
      for (size_t x = 0; x < 6; x++) {
        in >> graph[y][x];
        std::cout << graph[y][x] << ' ';
      }
      std::cout << '\n';
    }
  }
  return g;
}

int increment(int* ch, Matrix *c, Matrix *f, int s, int t) {
  int max = 0;
  int p = 0;
  int o = 0;
  int i = 0;
  while (ch[o]) o++;
  for (int j = 1; j<o; j++) {
    i = ch[j]-1;
    if(c->m[p][i]==0 && c->m[i][p]!=0) {
      std::cout << -(c->m[i][p]) << "  ("<<p<<" - "<<i<<")"<< '\n';
    } else {
      std::cout << c->m[p][i] << "  ("<<p<<" - "<<i<<")"<< '\n';
    }
    //std::cout << *ch << '\n';
    p = i;
  }
  return max;
}

void testIncre() {
  int ch[7] = {1,2,4,3,5,6,'\0'};
  Matrix *c = Matrix_read("graph.txt");
  Matrix *f = Matrix_init(V);
  std::cout << increment(ch,c,f,1,6) << '\n';
}

void testMatrix() {
    Matrix *m = Matrix_read("graph.txt");
    //Matrix *m = Matrix_read("graphe.txt");
    if(m != NULL) {
      std::cout << "The maximum possible flow is " <<  Matrix_fordFulkerson(m) << '\n';
    } else {
      std::cout << "Bad file !" << '\n';
    }
    //cout << "The maximum possible flow is " << fordFulkerson(m->m, 0, (m->sz)-1) << "\n";
    Matrix_print(m);
}

// Driver program to test above functions
int main()
{
    std::cout << " == test Matrix ==" << '\n';
    testMatrix();
    std::cout << " == test Incre ==" << '\n';
    testIncre();
    // std::cout << " == test Load ==" << '\n';
    // testLoad();
    // Let us create a graph shown in the above example
    // int graph[V][V] = { {0, 16, 13, 0, 0, 0},
    //                     {0, 0, 10, 12, 0, 0},
    //                     {0, 4, 0, 0, 14, 0},
    //                     {0, 0, 9, 0, 0, 20},
    //                     {0, 0, 0, 7, 0, 4},
    //                     {0, 0, 0, 0, 0, 0}
    //                   };

    // cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 5);

  //   int graph[V][V] = { {0, 3, 2, 2, 0, 0, 0, 0},
  //   {0, 0, 0, 0, 5, 1, 0, 0},
  //   {0, 0, 0, 0, 1, 3, 1, 0},
  //   {0, 0, 0, 0, 0, 1, 0, 0},
  //   {0, 0, 0, 0, 0, 0, 0, 4},
  //   {0, 0, 0, 0, 0, 0, 0, 2},
  //   {0, 0, 0, 0, 0, 0, 0, 4},
  //   {0, 0, 0, 0, 0, 0, 0, 0},
	// };

	//cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 7) << "\n";

    return 0;
}
