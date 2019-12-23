struct Complex { Cord x, y;
  Complex(Cord xx, Cord yy, bool isPolar = false) {
    if (isPolar) {
      x = xx * cos(yy); y = xx * sin(yy);
    } else { x = xx, y = yy; } }
  Complex(Point a, Point b) {
    x = b.x - a.x; y = b.y - a.y; }
  Cord mod() { return hypot(x, y); }
  Cord angle() {
    if (isZero(x)) return (y > 0 ? PI / 2 : -PI / 2);
    return atan(y / x); }
  void add(const Complex& b) { x += b.x; y += b.y; }
  void mult(const Complex& b) {
    Cord tx = x * b.x - y * b.y;
    Cord ty = x * b.y + y * b.x;
    x = tx, y = ty; }
  void rotate(Cord ang) { mult(Complex(1.0, ang, true)); }
  void scale(Cord len) { x *= len; y *= len; }
  void unit() { scale(1.0 / mod()); }
}; typedef Complex vect;
Cord dot(vect a, vect b) { return a.x * b.x + a.y * b.y; }
Cord cross(vect a, vect b) { return a.x * b.y - b.x * a.y; }
Cord angle(Point a, Point o, Point b) {
  auto oa = vect(o, a), ob = vect(o, b);
  oa.unit(); ob.unit(); return acos(dot(oa, ob)); }
