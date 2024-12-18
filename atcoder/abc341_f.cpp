#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second
using ll=long long;

vector<int> adj[5005],topo;
vector<pii> edge;
int W[5005];
ll A[5005],dp[5005],dp2[5005];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n,m; cin>>n>>m;
    edge.resize(m);
    for(auto &[u,v]:edge) cin>>u>>v;
    for(int i=1;i<=n;++i) cin>>W[i];
    for(int i=1;i<=n;++i) cin>>A[i];
    for(auto &[u,v]:edge){
        if(W[u]==W[v]) continue;
        if(W[u]<W[v]) swap(u,v);
        adj[u].eb(v);
    }
    topo.resize(n);
    iota(topo.begin(),topo.end(),1);
    sort(topo.begin(),topo.end(),[&](const int &l,const int &r){
        return W[l]<W[r];
    });
    for(auto &u:topo){
        dp[0]=0;
        for(int w=1;w<=W[u];++w) dp[w]=0;
        for(auto &v:adj[u]){
            for(int w=W[u];w>=W[v];--w){
                dp[w]=max(dp[w],dp[w-W[v]]+dp2[v]);
            }
        }
        dp2[u]=dp[W[u]-1]+1;
    }
    ll ans=0;
    for(int i=1;i<=n;++i) ans+=dp2[i]*A[i];
    cout<<ans;

    return 0;
}
