#include<bits/stdc++.h>
using namespace std;

struct fenwick{
    vector<int> bit;
    fenwick(int n=0){init(n);}
    void init(int n){bit.assign(n,0);}
    void upd(int i,int x){
        for(;i<bit.size();i+=i&-i) bit[i]+=x;
    }
    int qr(int i){
        int ret=0;
        for(;i>0;i-=i&-i) ret+=bit[i];
        return ret;
    }
    void upd(int l,int r,int x){ upd(l,x), upd(r+1,-x); }
    int qr(int l,int r){ return qr(r)-qr(l-1); }
    int search(int x)
        int pos=0,sum=0;
        for(int i=1<<31-__builtin_clz((int)bit.size()-1);i>0;i>>=1){
            if(pos+i<bit.size()&&sum+bit[pos+i]<x) pos+=i,sum+=bit[pos];
        }
        return pos+1;
    }
};
