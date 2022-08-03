经典题

## 版本一

现已丢失

## 版本二

```c++
for(int i=0;i<n;i++){
	while(!q.empty()&&a[i]>=q.back().val){
		
		for(int j=q.back().id;j<=i;j++){
			b[j]=max(q.back().val,a[j]);//(*)
		}
		q.pop_back();
	}
	q.push_back({a[i],i});
}
while(!q.empty()){
	b[q.back().id]=q.back().val;
	q.pop_back();
}
```

这个版本问题在`b[j]=max(q.back().val,a[j]);//(*)`，举个例子`3,2,4`去最大则变为`3,4,4`，然后这个版本最大的问题在于总是去进行模拟。

## 版本三

```c++
for(int i=0;i<n;i++){
	bool yp=0;
	int qp;
	while(!q.empty()&&a[i]>=q.back().val){
		// for(int j=q.back().id;j<=i;j++){
			// b[j]=max(q.back().val,a[j]);
		// }
		yp=1;
		qp=q.back().id;
		b[q.back().id]=q.back().val;
		b[i]=q.back().val;
		q.pop_back();
	}
	if(!q.empty() and yp){
		b[qp]=a[i];
		b[i]=a[i];
	}
	q.push_back({a[i],i});
}
for(int i=1;i<n-1;i++){
	if(b[i]==b[i-1])i++;//(*)
	else b[i]=max(b[i],b[i-1]);
}
for(int i=0;i<n;i++){
	b[i]=max(b[i],a[i]);
}
int sum=0;
for(int i=0;i<n;i++){
	sum+=(b[i]-a[i]);
}
```

应该是被`if(b[i]==b[i-1])i++;//(*)`卡掉了，这行纯属瞎猜的。

## final

```c++
#define val first
#define id second
#define start first
#define final second
typedef pair<int,int> pii;
struct WAY{
	int one,two,num;
};
class Solution {
public:
    int trap(vector<int>& a) {
        int n=a.size();
        vector<int>b(n,0);
        deque<pii>q;
        WAY way[n+3];
        memset(way,0,sizeof way);
        for(int i=0;i<n;i++){
            bool yp=0;
            int qp;
            while(!q.empty()&&a[i]>=q.back().val){
                yp=1;
                qp=q.back().id;
                way[q.back().id]=WAY{q.back().id,i-1,q.back().val};//先变成小点的，根据下面第三行再进行判断，跟下面i-1都是i本身不可以传递，最后max复原
                q.pop_back();
            }
            if(!q.empty() and yp){
                way[qp]=WAY{qp,i-1,a[i]};//假如刚pop了一些，后面的墙又高以现在为主。如7，3，4先开始置3。因为左边墙比较矮就置左边的比如7，3，2，2，4，那肯定将2变成3。然后呢？发现左边还有墙，如果左边墙够高是不被pop的，因此将3和2都变成4
            }
            if(!q.empty()&&a[i]<q.back().val){
                if(way[q.back().id+1].one>0){
                    if(a[i]>=way[q.back().id+1].num){//碰到相消的比如9，5，4，5，6，这里两个5消去后没有记录，然后6就没有发挥作用，这里判断一下。如果左边还有那就看下与他正右边的那个数比一下，有所提升，扩大范围，所以5和4都应该变成6
                        way[q.back().id+1].two=i-1;
                        way[q.back().id+1].num=a[i];
                    }
                }
            }
            q.push_back({a[i],i});
        }
        for(int i=0;i<n;i++){
            if(way[i].one!=i)continue;
            int wayto=way[i].two;
            for(int j=i;j<=wayto;j++){//快慢指针，速度还行
                b[j]=way[i].num;
            }
            i=wayto;
        }
        for(int i=0;i<n;i++){
            b[i]=max(b[i],a[i]);
        }
        int sum=0;
        for(int i=0;i<n;i++){
            sum+=(b[i]-a[i]);
        }
        return sum;
    }
};
```

终于调出来了，感觉面向样例编程？

~~暴力~~，单调队列+带模拟罢了。
