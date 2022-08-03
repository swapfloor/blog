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

这个版本问题在`b[j]=max(q.back().val,a[j]);//(*)`，举个例子`3,2,4`去最大则变为`3,4,4`，然后这个版本最大的问题在于总是去模拟。

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

