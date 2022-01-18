void mult(VI a, VI b) { const int n = a.size();
  FOR(i,0,n+1) { moba[popcnt[i]][i] = a[i]; 
  	mobb[popcnt[i]][i] = b[i];
  } //SOS DP for moba[i] and mobb[i] for all i
  FOR(i,0,LOGN) FOR(j,0,LOGN) FOR(k,0,n+1) {
    if((k >> j) & 1) { /*-= for inverse SOSDP*/
        moba[i][k] += moba[i][k ^ (1 << j)];
        mobb[i][k] += mobb[i][k ^ (1 << j)];
    }
  } // end SOSDP
  FOR(i,0,n+1) FOR(j,0,LOGN) { int res = 0;
    FOR(k,0,j+1) { res += moba[k][i] * mobb[j - k][i]; }
    mobc[j][i] = res;
  } //Inverse SOS DP mobc[i] for all i
  FOR(i,0,n+1) { result[i] = mobc[popcnt[i]][i]; }
}
