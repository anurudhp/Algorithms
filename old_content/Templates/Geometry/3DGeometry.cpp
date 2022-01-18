#define CPREF const point& // don't forget to undef!!!
#define eq(a,b) (fabs((a)-(b)) < EPS)
struct point { DBL x,y,z;
  point(){x=y=z=0;}
  point(DBL _x,DBL _y,DBL _z=0):x(_x),y(_y),z(_z){}
  point(CPREF p){x=p.x;y=p.y;z=p.z;}
  bool operator == (CPREF p) const {
    return eq(x,p.x) && eq(y,p.y) && eq(z,p.z);
  } bool operator < (CPREF p) const {
    if(eq(x,p.x) && eq(y,p.y)) {return z<p.z;}
    if(eq(x,p.x)) {return y<p.y;} return x<p.x;
  } point operator+ (CPREF p) const {
    return point(x+p.x,y+p.y,z+p.z);
  } point operator- (CPREF p) const {
    return point(x-p.x,y-p.y,z-p.z);
  } point operator* (DBL s) const {
    return point(x*s, y*s, z*s);
  } point operator/ (DBL s) const {
    return point(x/s, y/s, z/s);
  } DBL dot(CPREF p) const {
    return x*p.x + y*p.y + z*p.z;
  } point cross(CPREF p) const {
    return point(y*p.z-z*p.y, z*p.x-x*p.z, x*p.y-y*p.x);
  } DBL norm() const { return sqrt(dot(*this));
  } point unit() const { return *this / norm();
  } point project(CPREF p) const { return unit()*p.dot(unit());
  } point rotCCW(CPREF axis, DBL ang) const{return *this*cos(ang)
   + cross(axis)*sin(ang) + axis*dot(axis) * (1-cos(ang));
  }
} null;
DBL boxprod(CPREF a,CPREF b,CPREF c){return a.dot(b.cross(c));}
struct line { point a,b; // through a, along direction b
  line() {}
  line(CPREF x,CPREF y):a(x),b(y-x) {} // thru x,y
  bool parallel(const line& l) const {
    return b.cross(l.b)==null && !(b.cross(a-l.a) == null);
  } bool same(const line& l) const {
    return b.cross(l.b)==null && b.cross(a-l.a)==null;
  } bool intersect(const line& l, point& p) const {
    if(b.cross(l.b)==null || !eq(0.0, boxprod(l.a-a,b,l.b))) 
      return false;
    point t = b.cross(l.b);
    DBL k = boxprod(t, l.a-a, l.b) / t.dot(t);
    p = a + b*k;
    return true;
  } bool isSkew(const line& l) const { point tmp;
    return !parallel(l)&&!same(l)&&!intersect(l,tmp);
  }
}; struct plane{ //point and normal vector
  point a, n; plane(){}
  plane(CPREF p, CPREF q, CPREF r) { // thru 3 pts
    a = p;
    n = p.cross(q) + q.cross(r) + r.cross(p);
  } plane(line l1,line l2){
    a = l1.a; n = l1.b.cross(l2.b);
    if(n == null) n = l1.b.cross(l1.a - l2.a);
  } plane(const plane & p) {
    a = p.a; n = p.n;
  } DBL dist(CPREF p) const {
    return n.project(p).norm() - n.project(a).norm();
  } point project(CPREF p) const {
    point per = n.project(p);
    point par = p - per;
    return par + n * n.project(a).norm();
  }
};
#undef CPREF