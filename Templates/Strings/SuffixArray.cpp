const int N = (int)2e5 + 10;
const int LOGN = 22;
//SA[i] = i’th Lexicographically smallest suffix’s index.
int RA[LOGN][N],SA[N],tempSA[N],cnt[N],msb[N],LCP[LOGN][N],dollar[N];
void cSort(int l,int k,int n) { 
  SET(cnt,0);
  rep(i,0,n) cnt[(i+k<n?RA[l][i+k]:0)]++;
  int maxi=max(300,n),t;
  for(int i=0,sum=0;i<maxi;i++) {
    t = cnt[i], cnt[i] = sum, sum += t;// index
  }
  rep(i,0,n)tempSA[cnt[(SA[i]+k<n?RA[l][SA[i]+k]:0)]++]=SA[i];
  rep(i,0,n)SA[i]=tempSA[i];}//dollar[i]: next '$' in string.
void build_SA(string &s){
  int n = sz(s);
  rep(i,0,n) RA[0][i] = s[i], SA[i] = i;
  rep(i,0,LOGN-1){
    int k=(1<<i);
    if(k>=n)break;
    cSort(i,k,n);cSort(i,0,n);
    int rank=0;RA[i+1][SA[0]]=rank; 
    rep(j,1,n){
      if((RA[i][SA[j]]==RA[i][SA[j-1]])
        &&(RA[i][SA[j]+k]==RA[i][SA[j-1]+k])) 
	        RA[i+1][SA[j]]=rank;
      else RA[i+1][SA[j]]=++rank;
    }
  }
}
void build_msb(){
  int mx=-1;
  rep(i,0,N) {
    if(i>=(1<<(mx+1)))
      ++mx;msb[i]=mx;
}} 
void build_LCP(string& s){ 
  int n=sz(s);
  rep(i,0,n-1){
    int x=SA[i],y=SA[i+1],k,ret=0;
    for(k=LOGN-1;k>=0 && x<n && y<n;k--){
      if((1<<k)>=n) continue;
      if(RA[k][x]==RA[k][y]) x+=1<<k,y+=1<<k, ret+=1<<k;
    }
    if(ret>=dollar[SA[i]]-SA[i])ret=dollar[SA[i]]-SA[i];
    LCP[0][i]=ret;
  }
  LCP[0][n-1]=10*N;
  rep(i,1,LOGN){
    int add=(1<<(i-1));
    if(add>=n) break; 
    rep(j,0,n){
      if(j+add<n)LCP[i][j]=min(LCP[i-1][j],LCP[i-1][j+add]);
      else LCP[i][j]=LCP[i-1][j];
}}}
int lcp(int x,int y){ 
  if(x== y)return dollar[SA[x]]-SA[x];
  if(x>y)swap(x,y);--y;int idx=msb[y-x+1],sub=1<<idx;
  return min(LCP[idx][x],LCP[idx][y-sub+1]);}
bool equal(int i,int j,int p,int q){//usage: build_msb(),build_SA(s),
  if(j-i!=q-p)return false; int idx=msb[j-i+1],sub=1<<idx;
  return (RA[idx][i]==RA[idx][p])&&RA[idx][j-sub+1];}//build_LCP(s)
