2300012969 盛梓航
##### 1.
先考虑没有循环的程序：
基础关系抽象分析本质上与基于霍尔逻辑的最强后条件计算等价![[Pasted image 20241210114021.png|450]]
![[Pasted image 20241210114039.png|450]]
可以看出效果是一样的，精度相同

对于循环语句：
实际上还是等价的，只不过在基础关系抽象中，循环可能导致分析不收敛。而在最强后条件计算中，直接包括了循环次数任意的结果（除循环不终止）。仅从结果上看，最强后条件计算给出了更好的精度

可能两者给出的表达式都难以分析

##### 2.
不总是存在一个值 $k$，使得循环展开任意$l\geqslant k$ 次后的分析结果都和理想结果相同

比如 `wp(while(x < 10) {x = x + 2;}, x = 10)`，最弱前条件显然是 `x <= 10 and x%2==0` ，但由于迭代不收敛（如果是 `x = x + 1`，那么是收敛的，所以只展开有限次，只能得到形如
`x <= 2*i || x = 2*i + 2 || ... || x = 8 || x = 10` 的结果，也就是不精确

根本原因在于分析不收敛，并且无法判断循环执行的次数（任意），所以不总是存在一个值 $k$，使得循环展开任意$l\geqslant k$ 次后的分析结果都和理想结果相同
