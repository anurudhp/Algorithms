// using Vec = Vect<double>; // or any other type
bool CCW(Vec a, Vec b, Vec c) { return LESS(0, (b-a).cross(c-b)); }
bool CW(Vec a, Vec b, Vec c) { return LESS((b-a).cross(c-b), 0); }
bool cmp(const Vec& a, const Vec& b) { return LESS(a.x - b.x, 0); }
void ConvexHull(vector<Vec> &pts) {
  sort(ALL(pts), cmp); vector<Vec> up, dn;
  for (auto& p: pts) {
    while(SZ(up) > 1 && !CW(up[SZ(up) - 2], up.back(), p))
      up.pop_back();
    while(SZ(dn) > 1 && !CCW(dn[SZ(dn) - 2], dn.back(), p))
      dn.pop_back();
    up.PB(p);dn.PB(p);
  } pts = dn;
  for (int i = SZ(up) - 2; i >= 1; i--) pts.PB(up[i]);
}
template<typename T> // area of convex poly
T ConvexArea(const vector<Vect<T>> &pts) { // pts in CCW order
  T res = 0; REP(i, SZ(pts)) {
    res -= pts[i].cross(i==0 ? pts.back() : pts[i-1]);
  } return res / 2;
}