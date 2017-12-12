typedef long double coord;
const coord INF = 1e18, EPS = 1e-9, PI = acos(-1);
bool zero(coord val) { return abs(val) <= EPS; }

struct Point { coord x, y; };
typedef pair<Point, Point> Segment;

// Det:- +ve = cw, -ve = ccw, 0 = collinear
coord det(Point A, Point B, Point C) {
  return (A.y - B.y) * (C.x - B.x) - (C.y - B.y) * (A.x - B.x); }

inline coord dist2(Point a, Point b) {
  coord dx = a.x - b.x, dy = a.y - b.y;
  return (dx * dx + dy * dy);
}
inline coord dist(Point a, Point b) { return sqrt(dist(a, b)); }
