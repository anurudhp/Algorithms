#define vec Vect<T>
template<typename T> struct Vect { T x, y;
  vec(): x(0), y(0) {}
  vec(T a, T b): x(a), y(b) {};
  template<class D>
  explicit vec(const Vect<D>& v): x(v.x), y(v.y) {};
  vec operator+(const vec& v) const {return vec(x+v.x, y+v.y);}
  vec operator-(const vec& v) const {return vec(x-v.x, y-v.y);}
  vec operator*(T s) const { return vec(x*s, y*s); }
  vec operator/(T s) const { return vec(x/s, y/s); }
  T dot(const vec& v) const { return x * v.x + y * v.y; }
  T cross(const vec& v) const { return x * v.y - y * v.x; }
  T norm() const { return hypot(x, y); }
  vec unit() const { return *this / norm(); }
  vec rotCCW(T ang) const {
    return vec(x*cos(ang) - y*sin(ang), x*sin(ang) + y*cos(ang));
  }
};
template<typename T> struct Line {
  vec a, v; // l(r) = a + rv
  Line(const vec& p, const vec& q) { // through p,q
    a = p; v = q - p;
  } Line perpendicular(const vec& p) const { // perp through p
    return Line(p, p + v.rotCCW(PI/2));
  } bool intersect(const Line& o, vec& p) const {
    if (isZero(v.cross(o.v))) return false;
    T alpha = ((o.a - a) / (v.cross(o.v))).cross(o.v);
    p = a + v * alpha; return true;
  }
};
#undef vec