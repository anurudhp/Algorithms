template<typename T> struct Complex {
#define base Complex<T>
  base(T r=0,T i=0): re(r), im(i) {};
  base operator+(const base& o) const {
    return base(re + o.re, im + o.im);
  } base operator-(const base& o) const {
    return base(re - o.re,im - o.im);
  } base operator*(const base& o) const {
    return base(re*o.re - im*o.im, re*o.im + im*o.re);
  } base conj() const { return base(re, -im); } 
  base operator*(T s) const { return base(re*s, im*s); } 
  base operator/(T s) const { return base(re/s, im/s); } 
  T real() const { return re; }
  T imag() const { return im; } 
  private: T re, im;
#undef base
};