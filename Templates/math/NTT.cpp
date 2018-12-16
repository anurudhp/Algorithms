struct NTT{ int phi(int m){ int ans=m ;//set L=2^(max)>=max input size
for(int p=2;p*p<=m;++p) if(m%p==0) {while(m%p==0) m/=p ; ans -= ans/p ;}
 if(m>1) ans -= ans/m ; return ans ;}//set mod,r=g^((mod-1)/L),rinv=r^-1
const static int L=1<<19;int mod,r,rinv,w[L>>1],iw[L>>1] ; vi rev;
int gen(int m) {int p = phi(m) , t=p ; vi d ;for(int i=2;i*i<=t;++i) if(t%i==0){
while(t%i==0) t/=i; d.pb(i);} if(t!=1) d.pb(t) ; rep(i,2,m) { bool ans=1 ;
for(auto &it:d) if(pwmod(i,p/it,mod)==1) {ans=false;break;}if(ans) return i ;}}
  void prepower(){w[0]=iw[0]=1;//call prepower
rep(i,1,L>>1) w[i]=(w[i-1]*(ll)r)%mod,iw[i]=(iw[i-1]*(ll)rinv)%mod;}
void revb(int nl) { static int l=-1; if(nl==l) return; int t,j,k=0;l=nl;
rev.resize(l+1); while ((1 << k) < nl) ++k; FEN(i,l) { j=rev[i-1]; t=k-1;
while(t >= 0 && ((j >> t) & 1) ) j ^= (1<<t),--t;
if(t>=0) j ^= (1<<t), --t ; rev[i] = j;}}
void ntt(vi &poly,bool inv=false){int len,l,u,v; revb(sz(poly));
FN(i,sz(poly))if(rev[i]>i) swap(poly[i],poly[rev[i]]);
for(len = 2, l = 1; len<=sz(poly); len +=len, l +=l){
for(int i=0;i<sz(poly); i += len){int pi=0,add=L/len,*W =inv?iw:w ;
FN(j,l){ u=poly[i+j];v = ((ll)poly[i+j+l]*(ll)W[pi])%mod;
poly[i+j]=u+v<mod?u+v: u+v-mod;poly[i+j+l]=u-v>=0 ? u-v : u-v+mod ;
pi+=add; }}}if(inv){ int xrev = pwmod(sz(poly),mod-2,mod) ;
FN(i,sz(poly)) poly[i] = ((ll)poly[i]*(ll)xrev)%mod ;}}
vi multiply(vi &a,vi &b){int bi=1, sz1 = sz(a)+sz(b), rsz;
while((1<<bi)<sz1) ++bi; rsz = (1<<bi);
vi poly1(rsz,0) ;FN(i,sz(a)) poly1[i]=a[i] ;
vi poly2(rsz,0) ;FN(i,sz(b)) poly2[i]=b[i] ; ntt(poly1) ; ntt(poly2) ;
FN(i,rsz)poly1[i]=(poly1[i]*(ll)poly2[i])%mod ; ntt(poly1,1) ;return poly1;}} ;
