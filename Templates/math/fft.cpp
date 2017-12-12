// Make 2 vector<base> a and b with values: coefficient of x^0, x^1, x^2 ...
// Resize them to double the size as powers double after multiplication.
// Then call fft(a, 0) and fft(b, 0) to convert them to point form.
// Then multiply using ans[i] = a[i]*b[i].
// Then call fft(ans, 1) to get back to coefficient form.

#include <bits/stdc++.h>
#define fr(x) scanf("%d",&x)
using namespace std;
#define base complex<double>
const double PI=acos(-1);
vector<base> a, ans;

inline void fft(vector<base> &a, bool invert) {
	int logn=0, n=a.size();
	while((1<<logn)<n) ++logn;
	for(int i=1, j=0; i<n; ++i) {
		int bit = (n>>1);
		for(; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if(i < j)
			swap (a[i], a[j]);
	}
	for(int len=2;len<=n;(len<<=1)) {
		double ang = 2*PI/len;
		if(invert) ang = -ang;
		base wlen(cos(ang), sin(ang));
		for(int i=0; i<n; i+=len) {
			base w(1);
			for(int j=0; j<(len/2); ++j) {
				base u = a[i+j], v = w*a[i+j+len/2];
				a[i+j] = u+v;
				a[i+j+len/2] = u-v;
				w *= wlen;
			}
		}
	}
	if(invert) {
		for(int i=0; i<n; ++i) {
			a[i] /= n;
		}
	}
}

// This function exponentiates a polynomial to degree k.
inline void exp(int k) {
	ans.push_back(1);
	for(int i=0; k; ++i) {
		if(k&(1<<i)) {
			ans.resize(max(ans.size(),a.size()));
			a.resize(max(ans.size(),a.size()));
			a.resize(a.size()<<1);
			ans.resize(ans.size()<<1);
			fft(a, 0);
			fft(ans, 0);
			for(int i=0; i<ans.size(); ++i) {
				ans[i]*=a[i];
			}
			fft(ans, 1);
			for(int i=0; i<ans.size(); ++i) {
				if(real(ans[i])>0.5) ans[i]=1;
				else ans[i]=0;
			}
			fft(a, 1);
			k=(k^(1<<i));
		}
		else {
			a.resize(a.size()<<1);
		}
		fft(a, 0);
		for(int i=0;i<a.size();++i){
			a[i] = a[i]*a[i];
		}
		fft(a, 1);
		for(int i=0;i<a.size();++i){
			if(real(a[i])>0.5) a[i]=1;
			else a[i]=0;
		}
	}
}

int main(){
	int n, k, temp;
	fr(n);
	fr(k);
	a.resize(1024);
	for(int i=1; i<=n; ++i) {
		fr(temp);
		a[temp]=1;
	}
	exp(k);
	for(int i=0; i<ans.size(); ++i) {
		if(real(ans[i])>0.5) printf("%d ",i);
	}
	return 0;
}
