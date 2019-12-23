vector<Point> convexHull(vector<Point> P) {
  vector<Point> up, dn;
  sort(P.begin(), P.end(), compareX);
  for (auto& p: P) {
    while (up.size() > 1 && !cw(*(up.end() - 2), *(up.end() - 1), p))
      up.pop_back();
    while (dn.size() > 1 && !ccw(*(dn.end() - 2), *(dn.end() - 1), p))
      dn.pop_back();
    up.push_back(p); dn.push_back(p);
  }
  for (int i = dn.size() - 2; i > 0; i--) up.push_back(dn[i]);
  return up;
}
