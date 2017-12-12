typedef long double Coord;
const Coord INF = 1e18, EPS = 1e-9, PI = acos(-1);
bool zero(Coord val) { return abs(val) <= EPS; }

struct Point { Coord x, y; };
typedef pair<Point, Point> Segment;

// Det:- +ve = cw, -ve = ccw, 0 = collinear
Coord Determ(Point A, Point B, Point C) {
  return (A.y - B.y) * (C.x - B.x) - (C.y - B.y) * (A.x - B.x); }

inline Coord dist2(Point a, Point b) {
  Coord dx = a.x - b.x, dy = a.y - b.y;
  return (dx * dx + dy * dy);
}
inline Coord dist(Point a, Point b) { return sqrt(dist(a, b)); }
