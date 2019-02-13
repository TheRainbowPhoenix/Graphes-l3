/*
 * Awoo !
 *
 */
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

Matrix * Mtr;

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

bool in(int v, int *t, int sz) {
  for (size_t i = 0; i < sz; i++) {
    if(t[i]==v) return true;
  }
  return false;
}

bool haveSucc(int i, int j) {
  if(Mtr->m[i][j]!=0) return true;

  return false;
}

int ** MooreDijkstra(int s) {

  int sz = 8;
  int * G = new int[sz];
  for (size_t i = 0; i < sz; i++) G[i] = -1;
  G[0] = 1;
  int *d = new int[sz];
  int **pere = new int * [sz];
  for (size_t i = 1; i < sz; i++) d[i] = -1;
  for (size_t i = 0; i < sz; i++) pere[i] = 0;
  int j = 1;

  for (size_t l = 1; l < sz-1; l++) {
    for (size_t i = 0; i < sz-1; i++) {
      if(!in(i+1, G, sz) && haveSucc(i, j)) {
        printf("%d ", i);
      }
      printf("%d\n", i);
      /* code */
    }
    /* code */
  }

  return pere;
}

//MooreDijkstra()

int main(int argc, char const *argv[]) {
  Mtr = Matrix_read("graph.txt");
  Matrix_print(Mtr);
  MooreDijkstra(8);
  return 0;
}
