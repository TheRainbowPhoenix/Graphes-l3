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
#include <vector>
#include <fstream>
#include <limits>
#include <utility>

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> cPair;

bool comp = [](const pair<int, int> &a, const pair<int, int> &b) {return a.second > b.second; };

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
  //Mtr = Matrix_read("graph.txt");
  //Matrix_print(Mtr);
  //MooreDijkstra(8);

	int nodesCount = 1;
	int edgesCount = 1;

	vector<vector<cPair > > G(nodesCount);

	vector<int> d(nodesCount, numeric_limits<int>::max());
	vector<int> pere(nodesCount, -1);

	int o = 1; // start node
	int s = 0;

	d[o] = s;

	priority_queue<cPair, vector<cPair>, greater<cPair> > pq;

	pq.push(make_pair(o, s));

	while (!pq.empty()) {
		int v = pq.top().first;
    int w = pq.top().second;
		pq.pop();

		std::cout << "a" << '\n';

		if(w<=d[v]) {
			for (cPair & it : G[v]) {
				int v2 = it.first;
        int w2 = it.second;
				if(d[v] + w2 < d[v2]) { // d crash
					d[v2] = d[v] + w2;
					pere[v2] = v;
					pq.push(make_pair(v2, d[v2]));
				}
			}
		}
	}

	for (size_t i = 0; i <= nodesCount; ++i) {
		cout << "\n ⬗ Path from " << o << " to " << i << " cost " << d[i] << endl;

		cout << i;
    for (int p = pere[i]; p != -1; p = pere[p])
      cout << " ⮘ " << p;
		cout << endl;
	}

  return 0;
}
