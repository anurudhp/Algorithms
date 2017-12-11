typedef long double Cord;
const Cord INF = 1e18, EPS = 1e-9;
const Cord PI = acos(-1);
bool isZero(Cord val) { return (-EPS < val && val < EPS); }
Cord ABS(Cord val) { return val >= 0 ? val : -val; }

struct Point { Cord x, y; };
typedef pair<Point, Point> Segment;
typedef vector<Point> PointList;

bool compareX(const Point& a, const Point& b) {
  if (a.x == b.x) return a.y <= b.y;
  return a.x < b.x;
}
bool compareY(const Point& a, const Point& b) {
  if (a.y == b.y) return a.x <= b.x;
  return a.y < b.y;
}

// Det:- +ve = cw, -ve = ccw, 0 = collinear
Cord Determ(Point A, Point B, Point C) {
  return (A.y - B.y) * (C.x - B.x) - (C.y - B.y) * (A.x - B.x);
}

#define cw(...)   (Determ(__VA_ARGS__) > 0)
#define ccw(...)  (Determ(__VA_ARGS__) < 0)
#define cwl(...)  (Determ(__VA_ARGS__) >= 0)
#define ccwl(...) (Determ(__VA_ARGS__) <= 0)

Cord dist2(Point a, Point b) {
  Cord dx = a.x - b.x;
  Cord dy = a.y - b.y;
  return (dx * dx + dy * dy);
}
Cord dist2(Segment s) {
  return dist2(s.first, s.second);
}
Cord dist(Point a, Point b) {
  return sqrt(dist(a, b));
}
Cord dist(Segment s) {
  return dist(s.first, s.second);
}
