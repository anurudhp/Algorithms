const Segment InfSegment = {{-INF, -INF}, {INF, INF}};
coord adis2(coord a, coord b) { return (a - b) * (a - b); }

Segment closest_pair_rec(vector<Point> Px, vector<Point> Py) {
  int n = Px.size();
  if (n < 2) return InfSegment;
  if (n == 2) return make_pair(Px[0], Px[1]);

  int m = n / 2;
  vector<Point> Pxl(Px.begin(), Px.begin() + m), Pxr(Px.begin() + m, Px.end());
  vector<Point> Pyl, Pyr;
  Pyl.reserve(Pxl.size()); // prevent allocation/resize overhead
  Pyr.reserve(Pxr.size()); // --do--

  Point mid = Px[m];
  for (int i = 0; i < n; i++) {
    (compareX(Py[i], mid) ? Pyl : Pyr).push_back(Py[i]);
  }

  auto resl = closest_pair_rec(Pxl, Pyl);
  auto resr = closest_pair_rec(Pxr, Pyr);
  auto res = (dist2(resl) < dist2(resr)) ? resl : resr;
  coord mindis = dist2(res);

  Pxl.clear(); Pyl.clear();
  Pxr.clear(); Pyr.clear();

  vector<Point> Pys;
  Pys.reserve(n);
  for (auto& p: Py) {
    if (adis2(p.x, mid.x) <= mindis) Pys.push_back(p);
  }
  for (int i = 0; i < Pys.size(); i++) {
    for (int j = i + 1; j < Pys.size(); j++) {
      if (adis2(Pys[i].y, Pys[j].y) > mindis) break;
      if (dist2(res) > dist2(Pys[i], Pys[j])) {
        res = {Pys[i], Pys[j]};
      }
    }
  }
  return res;
}

Segment closest_pair(vector<Point> P) {
  vector<Point> Px(P), Py(P);
  sort(Px.begin(), Px.end(), compareX);
  for (int i = 0; i < Px.size() - 1; i++) {
    if (dist2(Px[i], Px[i + 1]) == 0) return {Px[i], Px[i + 1]};
  }
  sort(Py.begin(), Py.end(), compareY);
  return closest_pair_rec(Px, Py);
}
