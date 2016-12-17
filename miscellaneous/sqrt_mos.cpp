class SQRT_MOS {
public:
  void init();
  void add(int i);
  void rem(int i);

  struct Query {
    int l, r;
    int id;
  };
  int l, r, block, answer;

  vector<int> execute(vector<Query> Q) {
    for (int i = 0; i < Q.size(); i++) Q[i].id = i;
    sort(Q.begin(), Q.end(),
      [&, this](const Query& a, const Query& b) {
        if (a.l / this->block == b.l / this->block) return a.r < b.r;
        return a.l < b.l;
    });
    vector<int> answers(Q.size());
    init();
    for(auto q: Q) {
      while(l < q.l) rem(l++);
      while(l > q.l) add(--l);
      while(r < q.r) add(++r);
      while(r > q.r) rem(r--);
      answers[q.id] = answer;
    }
    return answers;
  }
};

/*
  inherit from SQRT_MOS and override init(), add() and rem()
  - init():
    - set l, r
    - set block (ie. block size = sqrt(total size))
    - set answer
  - add(i): add index i
  - rem(i): remove index i

  - Call execute(vector of queries)
    - returns a vector of answers
*/
