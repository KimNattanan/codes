#include "stdio.h"

int a[100005];

int main(){
  int Q; scanf("%d",&Q);
  while(Q--){
    int i,j,k;
    int n,m; scanf("%d%d",&n,&m);
    int ans=0;
    for(i=0;i<n;++i) scanf("%d",&a[i]);
    for(k=0;k<=m;++k){
      int sum=0;
      for(i=0;i<n;++i){
        int x=1;
        for(j=0;j<k;++j) x=(x*a[i])%3;
        sum=(sum+x)%3;
      }
      if(sum%3==0) ++ans;
    }
    printf("%d\n",ans);
  }
}