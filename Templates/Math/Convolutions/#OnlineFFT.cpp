void convolve(int al,int ar,int bl,int br) {//poly a from al to ar
  int n=1,sz=ar-al+br-bl+1;//poly b from bl to br
  while(n<sz) n<<=1; vector<fft::cd> a1(n),b1(n);
  FOR(i,al,ar+1) a1[i-al].r=/*a[i]*/; //dynamic poly
  FOR(i,bl,br+1) b1[i-bl].r=/*b[i]*/; //fixed poly
  //-> make fft/ntt call -> a1[i]=a1[i]*b1[i] -> inverse of a1
  FOR(i,0,sz) {int nxtind=al+bl+i;if(nxtind<=/*maxbound*/) c[nxtind]+=a1[i].r;}
} void solve() {
  // in the calling function :->multiply a(0) with b(1),b(2)
  FOR(i,1,/*maxbound*/) {//->multiply a(i) with b(1) and b(2), c is conv of a and b
  //c[i+1]+=a[i]*b[1],c[i+2]+=a[i]*b[2]
  for(int pw=2;i%pw==0 && pw+1<=/*bound*/;pw*=2) {//convolving blocks of size pw
    convolve(i-pw,i-1,pw+1,min(pw*2,/*bound*/)); } } }
