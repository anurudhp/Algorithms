int P[2*N];// P[i]: longest-len palin keeping i as center.if
string new_str(string& s) {// new_str()[i]='#'; even-length palin.
  string NEW;NEW+="@";NEW+="#";for(auto x:s)NEW+=x,NEW+="#";
  NEW+="$";return NEW;}//1)curr ind in right boundary, init with
int lps(string& s) { // mirror val of curr ind in actual string.
  string Q=new_str(s); int c=0,r=0;
  rep(i,1,sz(Q)-1) {//2) expand beyond current length (if possible) 
/*1*/if (i<r)P[i]=min(r-i,P[2*c-i]); //3) Update c, r
/*2*/while(Q[i+P[i]+1]==Q[i-P[i]-1])++P[i];// if the current
/*3*/if (i+P[i]>r)c=i,r=i+P[i];}//pal expand beyond right bound
  int ml=0,palc=0;rep(i,1,sz(Q)-1)if(P[i]>ml)ml=P[i],palc=i;
return ml;}// pal=s.substr((palc-1-ml)/2,ml);palc=palc/2-1;