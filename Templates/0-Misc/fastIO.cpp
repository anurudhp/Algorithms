inline int scan(){ bool y=0; int x=0; char c=getchar_unlocked();
while(c<'0'||c>'9'){ if(c=='-')y=1; c=getchar_unlocked();} 
while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar_unlocked();}
return y?-x:x; }
