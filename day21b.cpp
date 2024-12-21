#include "./setup.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

void dfs(vector<ll> &ssDist, vector<vector<ll>> &distController, vector<vector<pair<int,int>>> &adj, vector<bool> &visited, vector<int> &controllerSeq, int curr) {
  // handle current sequence
  ll cost = 0;
  for (int i = 1; i < (int)controllerSeq.size(); ++i) {
    cost += distController[controllerSeq[i-1]][controllerSeq[i]];
  }
  cost += distController[controllerSeq.back()][controllerSeq.front()];
  ssDist[curr] = min(ssDist[curr], cost);

  // extend sequence
  for (auto &[next, controllerInput] : adj[curr]) {
    if (visited[next]) continue;
    
    controllerSeq.push_back(controllerInput);
    visited[next] = true;
    dfs(ssDist, distController, adj, visited, controllerSeq, next);
    visited[next] = false;
    controllerSeq.pop_back();
  }
}

int main() {
  const ll INF = LLONG_MAX >> 1;

  // numeric keypad <-- robotB <--- robotA <-- you
  // for directional inputs:
  const int ADIR = 0;
  const int UP = 1;
  const int LEFT = 2;
  const int DOWN = 3;
  const int RIGHT = 4;

  // for numeric keypad (can just use the numbers directly)
  const int ANUM = 10;

  // setup adjacencies of buttons
  // stores both dest and required input to press on controlling keypad
  vector<vector<pair<int,int>>> dirAdj(5);
  vector<vector<pair<int,int>>> numAdj(11);
  auto addEdge = [&](vector<vector<pair<int,int>>> &adj, int a, int b, int controllerInput) {
    adj[a].emplace_back(b, controllerInput);
  };
  addEdge(dirAdj, ADIR, UP, LEFT);
  addEdge(dirAdj, ADIR, RIGHT, DOWN);
  addEdge(dirAdj, UP, ADIR, RIGHT);
  addEdge(dirAdj, UP, DOWN, DOWN);
  addEdge(dirAdj, LEFT, DOWN, RIGHT);
  addEdge(dirAdj, DOWN, LEFT, LEFT);
  addEdge(dirAdj, DOWN, UP, UP);
  addEdge(dirAdj, DOWN, RIGHT, RIGHT);
  addEdge(dirAdj, RIGHT, DOWN, LEFT);
  addEdge(dirAdj, RIGHT, ADIR, UP);
  addEdge(numAdj, 0, 2, UP);
  addEdge(numAdj, 0, ANUM, RIGHT);
  addEdge(numAdj, 1, 2, RIGHT);
  addEdge(numAdj, 1, 4, UP);
  addEdge(numAdj, 2, 0, DOWN);
  addEdge(numAdj, 2, 1, LEFT);
  addEdge(numAdj, 2, 3, RIGHT);
  addEdge(numAdj, 2, 5, UP);
  addEdge(numAdj, 3, 2, LEFT);
  addEdge(numAdj, 3, 6, UP);
  addEdge(numAdj, 3, ANUM, DOWN);
  addEdge(numAdj, 4, 1, DOWN);
  addEdge(numAdj, 4, 5, RIGHT);
  addEdge(numAdj, 4, 7, UP);
  addEdge(numAdj, 5, 2, DOWN);
  addEdge(numAdj, 5, 4, LEFT);
  addEdge(numAdj, 5, 6, RIGHT);
  addEdge(numAdj, 5, 8, UP);
  addEdge(numAdj, 6, 3, DOWN);
  addEdge(numAdj, 6, 5, LEFT);
  addEdge(numAdj, 6, 9, UP);
  addEdge(numAdj, 7, 4, DOWN);
  addEdge(numAdj, 7, 8, RIGHT);
  addEdge(numAdj, 8, 5, DOWN);
  addEdge(numAdj, 8, 7, LEFT);
  addEdge(numAdj, 8, 9, RIGHT);
  addEdge(numAdj, 9, 6, DOWN);
  addEdge(numAdj, 9, 8, LEFT);
  addEdge(numAdj, ANUM, 0, LEFT);
  addEdge(numAdj, ANUM, 3, UP);

  // robotA[i][j] = cost to move from i to j on robotA's keypad (including cost to press j)
  // robotB[i][j] = cost to move from i to j on robotB's keypad (including cost to press j)
  // numpad[i][j] = cost to move from i to j on numpad (including cost to press j)
  // handled by brute forcing all paths from A to B
  auto calcDist = [&](vector<vector<ll>> &distController, vector<vector<pair<int,int>>> &adj) -> vector<vector<ll>> {
    int n = adj.size();
    vector<vector<ll>> dist(n, vector<ll>(n, INF));

    vector<bool> visited(n);
    for (int i = 0; i < n; ++i) {
      vector<ll> &ssDist = dist[i]; // single source dist
      ssDist[i] = 1;
      vector<int> controllerSeq(1, ADIR);
      visited[i] = true;
      dfs(ssDist, distController, adj, visited, controllerSeq, i);
      visited[i] = false;
    }
    return dist;
  };

  vector<vector<ll>> self(5, vector<ll>(5, 1));
  vector<vector<vector<ll>>> robots(25);
  robots[0] = calcDist(self, dirAdj);
  for (int r = 1; r < (int)robots.size(); ++r) robots[r] = calcDist(robots[r-1], dirAdj);
  auto numpad = calcDist(robots.back(), numAdj);

  // handle inputs
  string s;
  ll sumComplexity = 0;
  while (cin >> s) {
    auto getId = [](char c) {
      return c == 'A' ? ANUM : c - '0';
    };
    int prev = ANUM;
    ll cost = 0;
    for (char c : s) {
      int curr = getId(c);
      cost += numpad[prev][curr];
      prev = curr;
    }
    ll numPart = stoll(s.substr(0, s.size() - 1));
    ll complexity = cost * numPart;
    sumComplexity += complexity;
  }
  cout << sumComplexity << endl;
}