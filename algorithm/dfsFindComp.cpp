//dfs寻找连通分量
const int MAXN=10010;
int n;
vi g[MAXN];
bool vis[MAXN];
vi comp;
void dfs(int u){
	vis[u]=true;
	comp.pb(u);
	for(auto v:g[u]){
		if(!vis[v]){
			dfs(v);
		}
	}
}
void seeseeneed(){
	rep(i,0,n)vis[i]=false;
	rep(i,0,n){
		if(!vis[i]){
			comp.clear();
			dfs(i);
			cout<<"Component:";
			rep(j,0,si(comp)){
				cout<<' '<<comp[j];
			}
			OUT();
		}
	}
}
