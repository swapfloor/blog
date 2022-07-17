int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}
