2300012969 盛梓航

### 1.
![[Pasted image 20241104224714.png]]


不存在，由于 $x$ 大小任意，对于任意 $k$ ，$x>k$ 的情况下 $k$ 深度的调用得不到精确结果，只会引入不可能路径的答案

### 2.
需要定义 $(f_1\sqcap f_2)(x)=f_1(x)\sqcap f_2(x)$

$$\begin{aligned}(f_1\sqcap f_2)(x)&=f_1(x)\sqcap f_2(x)\\&=(g_1\cup(x-k_1))\cap(g_2\cup(x-k_2))\\&=(g_1\cap g_2)\cup(g_1\cap (x-k_2))\cup((x-k_1)\cap g_2)\cup((x-k_1)\cap (x-k_2))\\&=(g_1\cap g_2)\cup((g_1-k_2)\cap x)\cup((g_2-k_1)\cap x)\cup(x-(k_1\cup k_2))\\&=(g_1\cap g_2)\cup(x-((k_1\cup k_2)-((g_1-k_2)\cup(g_2-k_1))))\end{aligned}$$

所以 $(g_1,k_1)\sqcap (g_2,k_2)=(g_1\cap g_2,(k_1\cup k_2)-((g_1-k_2)\cup(g_2-k_1)))$ 

复合操作是相同的  