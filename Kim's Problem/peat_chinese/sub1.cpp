#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pii=pair<int,int>;
#define f first
#define s second

vector<pii> adj[100005];

using A=pair<ll,int>;
priority_queue<A,vector<A>,greater<A>> pq;
ll dist[100005];
void dijk(){
    while(pq.size()){
        int u=pq.top().s;
        ll w=pq.top().f;
        pq.pop();
        if(dist[u]<w) continue;
        for(auto &vw:adj[u]){
            if(dist[vw.f]>w+vw.s){
                dist[vw.f]=w+vw.s;
                pq.emplace(dist[vw.f],vw.f);
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m,k; cin>>n>>m>>k;
    for(int i=0;i<m;++i){
        int u,v,w; cin>>u>>v>>w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    for(int i=2;i<=n;++i) dist[i]=LLONG_MAX;
    pq.emplace(0,1);
    dijk();
    for(int i=1;i<=n;++i) cout<<dist[i]<<'\n';

}