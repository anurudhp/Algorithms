vector<int> g[N], tree[N], rg[N], bucket[N];
int sdom[N],par[N],dom[N],dsu[N],label[N];
int arr[N],rev[N],T;//1-Based directed graph input
int Find(int u,int x=0){
  if(u==dsu[u])return x?-1:u;
  int v = Find(dsu[u],x+1);
  if(v<0)return u;
  if(sdom[label[dsu[u]]]<sdom[label[u]])
    label[u] = label[dsu[u]];
  dsu[u] = v;return x?v:label[u];
}
void Union(int u,int v){ //Add an edge u-->v
  dsu[v]=u; //yup,its correct :)
}
void dfs0(int u){
  T++;arr[u]=T;rev[T]=u;
  label[T]=T;sdom[T]=T;dsu[T]=T;
  for(auto w : g[u]){
    if(!arr[w])dfs0(w),par[arr[w]]=arr[u];
    rg[arr[w]].push_back(arr[u]);
}}
//Build Dominator tree(in main)
dfs0(1);n=T;
for(int i=n;i>=1;i--){
  for(int j=0;j<rg[i].size();j++)
    sdom[i] = min(sdom[i],sdom[Find(rg[i][j])]);
  if(i>1)bucket[sdom[i]].push_back(i);
  for(int j=0;j<bucket[i].size();j++){
    int w = bucket[i][j],v = Find(w);
    if(sdom[v]==sdom[w])dom[w]=sdom[w];
    else dom[w] = v;
  }
  if(i>1)Union(par[i],i);
}
for(int i=2;i<=n;i++){
  if(dom[i]!=sdom[i])dom[i]=dom[dom[i]];
  tree[rev[i]].push_back(rev[dom[i]]);
  tree[rev[dom[i]]].push_back(rev[i]);
}//done :)