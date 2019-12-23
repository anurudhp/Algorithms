#define Vec Vect<T>
template<typename T> struct Vect { T x, y;
  Vec(): x(0), y(0) {}
  Vec(T a, T b): x(a), y(b) {};
  template<class D>
  Vec(const Vect<D>& o): x(o.x), y(o.y) {};
  Vec operator+(const Vec& o) const {return Vec(x+o.x, y+o.y);}
  Vec operator-(const Vec& o) const {return Vec(x-o.x, y-o.y);}
  Vec operator*(T s) const { return Vec(x*s, y*s); }
  Vec operator/(T s) const { return Vec(x/s, y/s); }
  T dot(const Vec& o) const { return x * o.x + y * o.y; }
  T cross(const Vec& o) const { return x * o.y - y * o.x; }
  T norm() const { return hypot(x, y); }
  Vec unit() const { return *this / norm(); }
  Vec rotCCW(T ang) const {
    return Vec(x*cos(ang) - y*sin(ang), x*sin(ang) + y*cos(ang));
  }
};
template<typename T> struct Line {
  Vec a, v; // l(r) = a + rv
  Line(const Vec& p, const Vec& q) { // through p,q
    a = p; v = q - p;
  } Line perpendicular(const Vec& p) const { // perp through p
    return Line(p, p + v.rotCCW(PI/2));
  } bool intersect(const Line& o, Vec& p) const {
    if (isZero(v.cross(o.v))) return false;
    T alpha = ((o.a - a) / (v.cross(o.v))).cross(o.v);
    p = a + v * alpha; return true;
  }
};
#undef Vec