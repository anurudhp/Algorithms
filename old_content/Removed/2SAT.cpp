VVI adj; // indexing: var(i) = 2i, not(i) = 2i+1
void implies(int u, int v) { adj[u].PB(v); }
void add_or (int x, int y) { implies(1^x, y); implies(1^y, x); }
void add_xor(int x, int y) { add_or(x, y); add_or(1^x, 1^y); }
void add_eq (int x, int y) { add_xor(x, 1^y); }
void add_true(int x) { add_or(x, x); }
// Run SCC, assign true greedily in reverse toposort order
