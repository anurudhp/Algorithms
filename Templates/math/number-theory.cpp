tuple<LL,LL,LL> extended_euclid(LL a,LL b){
  LL s=0,ss=1,t=1,tt=0,r=b,rr=a;
  while(r){ LL tmp=ss-(rr/r)*s;
    ss=s;s=tmp;tmp=tt-(rr/r)*t;tt=t;t=tmp;tmp=rr%r;rr=r;r=tmp;
  } if(a<0){ss=-ss;tt=-tt;rr=-rr;} //ss*a+tt*b=rr=gcd(a,g)
  return make_tuple(ss,tt,rr); }
LL mod_inverse(LL a,LL n){ LL b,k,g;//ba+kn=gcd(a, n)
  tie(b,k,g)=extended_euclid(a,n);return (g!=1?-1:mod(b,n)); }
pair<LL,LL> chinese_remainder_theorem(LL x,LL a,LL y,LL b){
  // finds z (mod M) so z = a (mod x) and z = b (mod y)
  LL s,t,d;tie(s,t,d)=extended_euclid(x,y);
  if(a%d!=b%d)return make_pair(0,-1);LL M=x*y;
  LL z=(modmul(modmul(s,b,M),x,M)+modmul(modmul(t,a,M),y,M))%M;
  return make_pair(z/d,M/d); }
//returns x,y such that c=ax+by
pair<LL,LL> linear_diophantine(LL a,LL b,LL c){
  LL d = __gcd(a, b);
  if(c % d != 0) return make_pair(-1,-1);
  return make_pair((c/d)*mod_inverse(a/d,b/d),(c-a*x)/b); }
//returns all solutions to ax=b mod n
vector<int> modular_linear_equation_solver(int a,int b,int n){
  LL x,y,d;tie(x,y,d)=extended_euclid(a,n);
  vector<int> ans;
  if(b%d==0){ b/=d;n/=d;x=mod(x*b,n);
    for(LL i=0;i<d;++i)ans.push_back(mod(x+i*n,n));
  } return ans; }
