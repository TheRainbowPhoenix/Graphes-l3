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

	int u = 0;

	int pf = ch[t];
	int swp = pf;
	for (size_t v = t; v !=s; v=ch[v]) {
		u = ch[v];
		swp = (c->m[u][v])-(f->m[u][v]);
		if(swp<pf) pf=swp;
		//std::cout << "."<< swp << " - "<< v << '\n';
	}

	return pf;
}

int flotmax(Matrix *c, Matrix *f, int s, int t)
{

	int max_flow = 0;
	int i, j;

	int *ch = new int[c->sz];
	memset(ch, 0, sizeof(ch));
 
    while (chaineaugmentante(ch, c, f, s, t))
    {

    	int flow = increment(ch, c, f, s, t);

    	for (j=t; j!=s ; j=ch[j])
    	{
    		i = ch[j];
    		f->m[i][j] += flow;
    		f->m[j][i] -= flow;
    	}

    	max_flow += flow;
    }
 
    return max_flow;
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

void testflot() {
  Matrix *c = Matrix_read("graph.txt");
  Matrix *f = Matrix_fill(Matrix_init(6));
  int flow = flotmax(c,f,0,5);
  Matrix_print(c);
  cout << endl;
  Matrix_print(f);
  cout << endl;
  std::cout << "Flow max = " << flow << '\n';

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
    std::cout << " == test Flot max ==" << '\n';
    testflot();

    return 0;
}
