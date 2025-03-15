2300012969 盛梓航
```
struct Node{
	int value;
	Node* next;
};
a = malloc();
b = malloc();
a->next = b;
b->next = malloc();
```

从上往下对每条语句有：
$\{1\}\subseteq \boldsymbol{a}$
$\{2\}\subseteq \boldsymbol{b}$

$\boldsymbol{b}\subseteq \boldsymbol{a}\to\boldsymbol{next}$
$\boldsymbol{b}\to\boldsymbol{next}\subseteq \boldsymbol{a}\to\boldsymbol{next}$
$\boldsymbol{a}\to\boldsymbol{next}\subseteq \boldsymbol{b}\to\boldsymbol{next}$

$\{3\}\subseteq \boldsymbol{b}\to\boldsymbol{next}$

画出可达性图
![[Pasted image 20241118160836.png|500]]


