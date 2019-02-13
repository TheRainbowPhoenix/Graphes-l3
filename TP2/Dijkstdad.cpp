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

int ** MooreDijkstra(int s) {

  int sz = 8;
  int * G = new int[sz];
  G[0] = 1;
  int *d = new int[sz];
  int **pere = new int * [sz];
  for (size_t i = 1; i < sz; i++) d[i] = -1;
  for (size_t i = 0; i < sz; i++) pere[i] = 0;
  int j = 1;

  return pere;
}

//MooreDijkstra()

int main(int argc, char const *argv[]) {
  Matrix *c = Matrix_read("graph.txt");
  Matrix_print(c);
  return 0;
}
