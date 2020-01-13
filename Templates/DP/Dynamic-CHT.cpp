const DBL INF = 1e16;
struct HullDynamic {
#define CLREF const Line&
  struct Line { int a; LL b, val=0; DBL xLeft = -INF; bool type=0;
    Line(LL a = 0, LL b = 0): a(a), b(b) {}
    LL eval(int x) const{ return a * 1ll * x + b; }
    bool operator< (CLREF l2) const {
      return l2.type ? (xLeft > l2.val) : (a < l2.a);
    }
  }; using ITER = set<Line>::iterator;
  bool parallel(CLREF l1, CLREF l2) { return l1.a == l2.a; }
  DBL meetX(CLREF l1, CLREF l2) {
    return parallel(l1, l2) ? INF : (l2.b-l1.b) / (DBL(l1.a-l2.a));
  } set<Line> hull;
  bool hasPrev(ITER it) { return it != hull.begin();
  } bool hasNext(ITER it) {
    return it != hull.end() && next(it) != hull.end();
  } bool bad(CLREF l1, CLREF l2, CLREF l3){
    return meetX(l1,l3) <= meetX(l1,l2);
  } bool bad(ITER it) { return hasPrev(it) && hasNext(it)
                      && (bad(*next(it), *it, *prev(it)));
  } ITER upd_left_border(ITER it) {
    if(!hasNext(it)) return it;
    DBL val = meetX(*it, *next(it));
    Line buf(*it); it = hull.erase(it);
    buf.xLeft = val; it = hull.insert(it, buf); return it;
  } void insert_line(int a, LL b) {
    Line l3 = Line(a, b); auto it = hull.lower_bound(l3);
    if(it != hull.end() && parallel(*it , l3)) {
      if (it->b > b) it = hull.erase(it);
      else return;
    } it = hull.insert(it, l3);
    if(bad(it)) { hull.erase(it); return; }
    while(hasPrev(it) && bad(prev(it))) hull.erase(prev(it));
    while(hasNext(it) && bad(next(it))) hull.erase(next(it));
    it = upd_left_border(it);
    if(hasPrev(it)) upd_left_border(prev(it));
    if(hasNext(it)) upd_left_border(next(it));
  } LL eval(int x) {
    Line q; q.val = x; q.type = 1; auto best = hull.lower_bound(q);
    return (best == hull.end()) ? INF : best->eval(x);
  }
};