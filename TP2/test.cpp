#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

typedef pair<int, int> cPair;

int main() {

  ifstream f("djk.txt", ios::in);
  if (!f) return 1;
  cin.rdbuf(f.rdbuf());

  int nodesCount, edgesCount;
  cin >> nodesCount >> edgesCount;

  vector<vector<cPair > > G(nodesCount);

  for (int i = 0; i != edgesCount; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    G[u].push_back(make_pair(v, w));
  }

  int o;
  cin >> o;

  vector<int> d(nodesCount, 9000);

  d[o] = 0;

  vector<int> pere(nodesCount, -1);

  priority_queue<cPair, vector<cPair>, greater<cPair> > pq;
  pq.push(make_pair(o, d[o]));

  while (!pq.empty()) {
    int v = pq.top().first;
    int w = pq.top().second;
    pq.pop();

    if (w <= d[v]) {
      for (auto & i : G[v]) {
        int v2 = i.first;
        int w2 = i.second;
        if (d[v] + w2 < d[v2]) {
          d[v2] = d[v] + w2;
          pere[v2] = v;
          pq.push(make_pair(v2, d[v2]));
        }
      }
    }
  }

  for (size_t i = 0; i <= nodesCount; ++i) {
		cout << "\nPath from " << o << " to " << i << " cost " << d[i] << endl;

		cout << "  " <<i;
    for (int p = pere[i]; p != -1; p = pere[p])
      cout << " ↼ " << p;
		cout << endl;
	}
}
