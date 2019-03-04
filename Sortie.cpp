#include <bits/stdc++.h>
#define NMAX 100005
#define inf (LLONG_MAX>>2)
#define ll long long
int c[NMAX], d[NMAX];
int sz = 32;
using namespace std;
int ok(int x){
	ll eq = 0;
	for(int i = 0, j = 0; i<x; i++){
		j = max(j,d[i]);
		ll u  = (1LL)<<d[i];
		if(eq >=u ) 
			eq -= u , u = 0; 
		else
		for(;j<= sz;j++){
			if(c[j]-->0){
				eq = (1LL)<<j;
				if(eq>=u)eq -=u,u = 0;
			}
			if(u<=0)break;
		}
		if(u>0)return i;
	}
	return x;
}
void solve() {
    int n,m;
    scanf("%d %d",&n,&m);
    memset(d,0,sizeof(d));
    memset(c,0,sizeof(d));
    int imax = 0;
    for(int i = 0;i<n;i++){
    	ll x;scanf("%lld",&x);
    	for(int i = 0;x>>i;i++)
    		c[i] += (x>>i)&1; 
    }
    for(int i = 0;i<m;i++) scanf("%d",&d[i]);
    sort(d,d+m);
	printf("%d\n",ok(m));
}
int main(){
	int tc;scanf("%d",&tc);
	while(tc--)solve();
}
