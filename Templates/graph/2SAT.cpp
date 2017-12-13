// 2-SAT: compute SCCs. if x & !x are in same SCC, then not possible
// else assign values (pref. false) in toposort order
// impl. trick (node nos.): x_i = 2*i, x_i' = 2*i+1
[u => v: edge u --> v]
[u or v: ~u => v, ~v => u]
[u xor v: u => ~v, v => ~u, ~u => v, ~v => u]
[u eq v: u => v, v => u, ~u => ~v, ~v => ~u]
[u: u or u];
