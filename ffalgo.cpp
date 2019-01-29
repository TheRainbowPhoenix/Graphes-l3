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

Matrix * Matrix_fill(Matrix *m) {
  for (size_t x = 0; x < m->sz; x++) {
    for (size_t y = 0; y < m->sz; y++) {
      m->m[x][y] = 0;
    }
  }
  return m;
}

void Matrix_print(Matrix *m) {
  for (size_t x = 0; x < m->sz; x++) {
    for (size_t y = 0; y < m->sz; y++) {
      std::cout << m->m[x][y] << ' ';
    }
    std::cout << '\n';
  }
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

// Renvoi si une chaine augmentante existe d'un sommet S à T
bool chaineaugmentante(int * ch, Matrix * c, Matrix * f, int s, int t)
{
    // Tableau de sommets visité initialisé à 0
    bool * visited = new bool[c->sz];
    memset(visited, 0, sizeof(visited));

    // Création de la pile, on rajoute le noeud source
    queue <int> p;
    ch[s] = -1;
    p.push(s);

    bool stop = false;

    while (!p.empty() && !stop)
    {
        int i = p.front();
        p.pop();

        if (i == t) // Si on est arrivé avec le parcours on arrête les machines
        {
          visited[i] = true;
          stop = true;
        }
        else if (visited[i] == false) // On fais un parcours en profondeur en regardant si le chemin respecte les conditions d'une Chaine Augmentante
        {
          visited[i] = true;
          for (int j=0; j<c->sz; j++)
          {
            if (visited[j] == false)
            {
              if ((c->m[i][j] > 0 && c->m[i][j] > f->m[i][j]) || (c->m[j][i] > 0 && f->m[j][i] > 0))
              {
                p.push(j);
                ch[j] = i;
              }
            }
          }
        }
    }
    return (visited[t] == true); // Si on est bien arrivé à destination, ding ding Chaine augmentante !
}

int increment(int* ch, Matrix *c, Matrix *f, int s, int t) {
  int p = 0;
  int o = 0;
  int i = 0;
  int flx = 0;
  int j = 1;
	int n = t;
	int flag = 0;
	int min = ch[n];
	while(ch[n] != n && n>=0) {
		n = ch[n];
		if(n<min && n>0) min = n;
		//std::cout << " "<< n << '\n';
	}
	return min;

  //int min = c->m[p][ch[1]-1];
  /*while (ch[o]) {
    if(ch[o]==s+1) j = o;
    o++;
  }
  for (j; j<o; j++) {
    i = ch[j]-1;
    // Get the available flot between two points
    flx = (c->m[p][i]>0)?(c->m[p][i]):((c->m[i][p]!=0)?(-(c->m[i][p])):(c->m[p][i]))-(f->m[p][i]);
    if(min>flx && flx >= 0) min=flx;
    //std::cout << flx << "  ("<<p<<" - "<<i<<")"<< '\n';
    p = i;
    if(ch[j] == t) break;
  }
  return min;*/
}

void testCA()
{
  int ch[6] = {-1,-1,-1,-1,-1,-1};
  Matrix *c = Matrix_read("graph.txt");
  Matrix *f = Matrix_fill(Matrix_init(6));
  bool bch = false;
  bch = chaineaugmentante(ch, c, f, 0, 5);

  for (int i=0;i<6;++i)
  {
    cout << ch[i] << ' ';
  }

  cout << endl << ((bch)?"Chaine augmentante":"Pas de chaine augmentante") << endl;
}

void testIncre() {
  int ch[6] = {-1,0,0,2,2,4};
  Matrix *c = Matrix_read("graph.txt");
  Matrix *f = Matrix_fill(Matrix_init(6));
  std::cout << increment(ch,c,f,0,5) << '\n';
}

void testMatrix() {
    Matrix *m = Matrix_read("graph.txt");
    //Matrix *m = Matrix_read("graphe.txt");
    if(m != NULL) {
      //std::cout << "The maximum possible flow is " <<  Matrix_fordFulkerson(m) << '\n';
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
    std::cout << " == test Chaine Augm. ==" << '\n';
    testCA();
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
