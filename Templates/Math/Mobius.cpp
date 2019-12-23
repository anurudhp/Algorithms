vi MF(int N) {//return vector with mobious inverse of 1->N
    vi MB(N+1,0) ; ll temp ;
    MB[1] = 2 ;
    rep(i,2,N+1) if(!MB[i]) {
        MB[i] = 1 ; temp = (ll)i*(ll)i ;
        if(temp<=N) for(int j=temp ;j<=N;j+=temp) MB[j]=-1 ;
        for(int j = i<<1;j<=N;j+=i) if(MB[j]!=-1) ++MB[j] ;
    } FEN(i,N)  MB[i]=(MB[i]==-1)?0:(MB[i]&1)?-1:1;
    return MB ;
}vi dirichletConv(vi &A,vi &B,int N){//H(n)=sum(x,y:x*y=n) A[x]*B[y]for[1,N]
    vi ans(N+1,0) ;
    FEN(i,N)for(int j=i;j<=N;j+=i)ans[j]+=A[i]*B[j/i] ;
    return ans ;
}
