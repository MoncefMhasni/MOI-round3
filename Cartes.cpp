#include <bits/stdc++.h>
const int NMAX = 1e5+5;
using namespace std;
int main(){
	int tc;scanf("%d",&tc);
	while(tc--){
	int N,M;scanf("%d %d",&N,&M);
	set<int> s;
	int arr[NMAX];
	for(int i = 0;i < N;i++)s.insert(s.end(),i), arr[i] = i+1;
	while(M--){
		int a,b,c;scanf("%d %d %d",&a,&b,&c);
		auto r = s.lower_bound(a-1);
		for (; r!= s.end() && *r >= a-1 && *r <= b-1;){
            if(*r == c-1) r++;
            else {
            arr[*r] = c;
            r = s.erase(r);
            }
        }
	}
	for(int i = 0;i<N;i++)printf("%d ",arr[i]);
	printf("\n");
	}
}
