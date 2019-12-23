// using Vec = Vect<double>; // or any other type
bool CCW(Vec a, Vec b, Vec c) { return (b-a).cross(c-b) > 0; }
bool CW(Vec a, Vec b, Vec c) { return (b-a).cross(c-b) < 0; }
bool cmp(const Vec& a, const Vec& b) { return a.x - b.x < 0; }
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