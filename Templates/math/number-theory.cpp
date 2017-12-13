tuple<LL, LL, LL> extended_euclid(LL a, LL b) { // ax + by = gcd(a, b)
  LL x0 = 1, x1 = 0, y0 = 0, y1 = 1, r0 = a, r1 = b;
  while (r1 != 0) { LL q = r0 / r1, temp;
    temp = r1, r1 = r0 - q * r1, r0 = temp;
    temp = x1, x1 = x0 - q * x1, x0 = temp;
    temp = y1, y1 = y0 - q * y1, y0 = temp;
  }
  return make_tuple(x0, y0, g); // gcd(a, b) = r0
}

LL mod_inverse(LL a, LL n) { // returns -1 if mod_inv doesn't exist
  LL b, g;
  tie(b, IGNORE, g) = extended_euclid(a, n, g);
  return g == 1 ? ((b % n) + n) % n : -1;
}

pair<LL,LL> chinese_remainder_theorem(LL x,LL a,LL y,LL b){
  // finds z (mod M) so z = a (mod x) and z = b (mod y)
  LL s,t,d;tie(s,t,d)=extended_euclid(x,y);
  if(a%d!=b%d)return make_pair(0,-1);LL M=x*y;
  LL z=(modmul(modmul(s,b,M),x,M)+modmul(modmul(t,a,M),y,M))%M;
  return make_pair(z/d,M/d);
}

//returns x,y such that c=ax+by
pair<LL,LL> linear_diophantine(LL a,LL b,LL c){
  LL d = __gcd(a, b);
  if(c % d != 0) return make_pair(-1,-1);
  return make_pair((c/d)*mod_inverse(a/d,b/d),(c-a*x)/b);
}

//returns all solutions to ax=b mod n
vector<int> modular_linear_equation_solver(int a,int b,int n){
  LL x,y,d;tie(x,y,d)=extended_euclid(a,n);
  vector<int> ans;
  if(b%d==0){
    b/=d;n/=d;x=mod(x*b,n);
    for(LL i=0;i<d;++i)ans.push_back(mod(x+i*n,n));
  }
  return ans;
}
