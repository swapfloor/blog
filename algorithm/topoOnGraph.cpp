vi a[V];//邻接表
bool vis[V];
vi ans;
int cnt;
void topo(int u,vi a[]){
  vis[u]=true;
  for(auto v:a[u]){
    if(!vis[v]){
      topo(v,a);//先dfs到没有出度的点，将该点添加到栈中，这样优先级高的先入栈，最后取出
    }
  }
  ans[--cnt]=u;
}
int main(){
  INT(V);
  ans.resize(V);
  cnt=V;
  rep(i,0,V){
    if(!vis[i]){
      topo(i,a);//有些点可能不在一个群内部，所有不能用dfs搜到，我们添加一个vis数组去记录已经遍历的点。
    }
  }
}
