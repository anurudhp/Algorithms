typedef long long Cord;
struct Point {
  Cord x, y;
};
const Cord INF = 1e9;
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

Cord dist(Point a, Point b) {
  Cord dx = a.x - b.x;
  Cord dy = a.y - b.y;
  return (dx * dx + dy * dy);
}
Cord dist(Segment s) {
  return dist(s.first, s.second);
}
