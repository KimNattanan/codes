#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
#define eb emplace_back
using pii=pair<int,int>;
#define f first
#define s second

const ll md=998244353;

int n;
vector<int> H,lm,rm;

struct segment2{
    struct node{
        node *L,*R;
        ll sum;
        int lz;
        node():L(nullptr),R(nullptr),sum(0),lz(0){}
    };
    using pnode=node*;
    vector<pnode> rt;
    int l0,r0;
    void build(pnode &t,int il,int ir){
        t=new node();
        if(il==ir) return;
        build(t->L,il,(il+ir>>1)),build(t->R,(il+ir>>1)+1,ir);
    }
    void build(int n,int l,int r){
        rt=vector<pnode>(n+1);
        l0=l,r0=r;
        build(rt[0],l,r);
    }
    void flush(pnode t,int &il,int &ir){
        if(t&&t->lz){
            if(il!=ir){
                t->L=new node(*(t->L));
                t->R=new node(*(t->R));
                t->L->lz+=t->lz;
                t->R->lz+=t->lz;
            }
            t->sum+=(ir-il+1)*t->lz;
            t->lz=0;
        }
    }
    void upd(pnode t0,pnode &t1,int il,int ir,int &l,int &r){
        flush(t0,il,ir);
        if(il>r||ir<l) return void(t1=t0);
        if(l<=il&&ir<=r){
            t1=new node(*t0);
            ++t1->lz;
            flush(t1,il,ir);
            return;
        }
        t1=new node();
        upd(t0->L,t1->L,il,(il+ir>>1),l,r);
        upd(t0->R,t1->R,(il+ir>>1)+1,ir,l,r);
        t1->sum=t1->L->sum+t1->R->sum;
    }
    void upd(int prev,int now,int &l,int &r){upd(rt[prev],rt[now],l0,r0,l,r);}
    ll qr(pnode t,int il,int ir,int &l,int &r){
        if(il>r||ir<l) return 0;
        flush(t,il,ir);
        if(l<=il&&ir<=r) return t->sum;
        return qr(t->L,il,(il+ir>>1),l,r)+qr(t->R,(il+ir>>1)+1,ir,l,r);
    }
    ll qr(int now,int l,int r){return qr(rt[now],l0,r0,l,r);}
}t2;

ll play(int l,int r,int mid,int &h){
    if(l>r) return 1;
    if(H[mid]>=h) return (play(l,mid-1,lm[mid],H[mid])*play(mid+1,r,rm[mid],H[mid]))%md;
    return ((t2.qr(r,H[mid]+1,h)-t2.qr(l-1,H[mid]+1,h))%md+(play(l,mid-1,lm[mid],H[mid])*play(mid+1,r,rm[mid],H[mid]))%md)%md;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);

    cin>>n;
    H=lm=rm=vector<int>(n+1);
    for(int i=1;i<=n;++i) cin>>H[i];
    int mx=0;
    vector<pii> vec(n);
    for(int i=1;i<=n;++i){
        cin>>vec[i-1].f>>vec[i-1].s;
        mx=max(mx,vec[i-1].s);
    }
    t2.build(n,1,mx);
    for(int i=1;i<=n;++i) t2.upd(i-1,i,vec[i-1].f,vec[i-1].s);
    H[0]=1e9;
    stack<int> st;
    st.emplace(0);
    for(int i=1;i<=n;++i){
        while(H[st.top()]<H[i]) st.pop();
        lm[i]=rm[st.top()];
        rm[st.top()]=i;
        st.emplace(i);
    }

    cout<<play(1,n,rm[0],mx);

    return 0;
}
