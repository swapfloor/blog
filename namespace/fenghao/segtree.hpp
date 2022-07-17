#ifndef FENGHAO_SEGTREE_HPP
#define FENGHAO_SEGTREE_HPP 1

#include <vector>
using std::vector;

namespace fenghao {

    struct segtree{
    public:
        segtree(int _n) {
            N = 2 * _n;
            n = _n;
            t.assign(N, 0);
        }
        segtree(int _N, int _n){
            N = _N;
            n = _n;
            t.assign(N, 0);
        }
        int N;  // limit for array size
        int n;  // array size
        vector<int> t;

        void build() {  // build the tree
            for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
        }

        void modify(int p, int value) {  // set value at position p
            for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
        }

        int query(int l, int r) {  // sum on interval [l, r)
            int res = 0;
            for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                if (l&1) res += t[l++];
                if (r&1) res += t[--r];
            }
            return res;
        }
    };
}

#endif