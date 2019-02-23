#include <bits/stdc++.h>
using namespace std;

const int maxn = 300005, maxlg =  20;
int in[maxn], f[maxn], c[maxn], st[maxn][maxlg], d[maxn], id;
bitset<maxn> seen;
vector<int> g[maxn], t[maxn];
set<pair<int,int> > bridges;

void get(int cur, int par){
  seen[cur] = true;
  in[cur] = f[cur] = ++id;
  for(int i=0 ; i<g[cur].size() ; i++){
    int v = g[cur][i];
    if(v == par) continue;
    if(seen[v]) f[cur] = min(f[cur], in[v]);
    else{
      get(v, cur);
      f[cur] = min(f[cur], f[v]);
      if(f[v]>in[cur]){
        bridges.insert({min(v, cur), max(v, cur)});
      }
    }
  }
}

void dfs(int cur, int color, int par){
  c[cur] = color;
  for(int i=0 ; i<g[cur].size() ; i++){
    int v = g[cur][i];
    if(v == par || c[v] != 0 || bridges.find({min(cur, v), max(cur, v)}) != bridges.end()) continue;
    dfs(v, color, cur);
  }
}

void work(int cur, int par){
  d[cur] = d[par]+1;
  st[cur][0] = par;
  for(int i=0 ; i<t[cur].size() ; i++){
    if(t[cur][i] == par) continue;
    work(t[cur][i], cur);
  }
}

void build(int n){
  work(1, 0);
  for(int j=1 ; j<maxlg ; j++){
    for(int i=1 ; i<=n ; i++){
      if(st[i][j-1]) st[i][j] = st[st[i][j-1]][j-1];
    }
  }
}

int lca(int u, int v){
  if(d[u]<d[v]) swap(u, v);
  while((d[u]-d[v])>0){
    int up = log2(d[u]-d[v]);
    u = st[u][up];
  }
  if(u == v) return u;
  for(int j=maxlg-1 ; j>=0 ; j--){
    if(st[u][j] != st[v][j]) u = st[u][j], v = st[v][j];
  }
  return st[u][0];
}

int main(){
  int m, n, q;
  scanf("%d%d%d", &n, &m, &q);
  while(m--){
    int x, y;
    scanf("%d%d", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  get(1, 0);
  id = 0;
  for(int i=1 ; i<=n ; i++){
    if(c[i] == 0) dfs(i, ++id, 0);
  }
  for(auto it = bridges.begin() ; it != bridges.end() ; ++it){
    int x = c[(*it).first], y = c[(*it).second];
    t[x].push_back(y);
    t[y].push_back(x);
  }
  build(id);
  while(q--){
    int u, v, w;
    scanf("%d%d", &u, &v);
    u = c[u];
    v = c[v];
    w = lca(u, v);
    printf("%d\n", d[u]+d[v]-2*d[w]);
  }
  return 0;
}
