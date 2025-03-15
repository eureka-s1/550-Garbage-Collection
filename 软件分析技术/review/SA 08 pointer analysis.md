
### 过程内
##### 指向分析
指针变量可能指向的地址

先考虑流非敏感指向分析，先不考虑在堆上分配的内存，不考虑struct、数组等结构，不考虑指针运算，如 `*(p+1)`

##### Anderson 指向分析算法
	Inclusion-based
	
$a$：变量 $a$ 的地址
$\boldsymbol{a}$：指针 $a$ 所指向的集合

| 赋值语句   | 约束                                                                  |
| ------ | ------------------------------------------------------------------- |
| `a=&b` | $\{b\}\subseteq\boldsymbol{a}$                                      |
| `a=b`  | $\boldsymbol{b}\subseteq\boldsymbol{a}$                             |
| `a=*b` | $\forall v\in\boldsymbol{b},\boldsymbol{v}\subseteq\boldsymbol{a}$  |
| `*a=b` | $\forall v\in \boldsymbol{a},\boldsymbol{b}\subseteq\boldsymbol{v}$ |

由约束导出方程组，但每次都重新计算所有公式效率不高， 某个集合变化后，更新受影响的集合即可

对于每条边来说，前驱集合新增元素的时候该边将被激活，激活后执行时间为 $O(m)$，其中 $m$ 为新增的元素数量 
- 应用均摊分析，每条边传递的总复杂度为 $O(n)$，其中 $n$ 为结点数量 

边的数量为$O(n^2)$ ，总复杂度为 $O(n^3)$

进一步优化 
- 强连通子图中的每个集合必然相等 
- 动态检测图中的强连通子图，并且合并成一个集合

##### 流敏感的指针分析算法
转换成数据流分析

半格：指针变量到地址集合的映射
交汇：对应地址集合取并

| 赋值语句   | 转换函数                                                                                                                                                                                                                                                       |
| ------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `a=&b` | $f(V)=V[\boldsymbol{a}\mapsto\{b\}]$                                                                                                                                                                                                                       |
| `a=b`  | $f(V)=V[\boldsymbol{a}\mapsto\boldsymbol{b}]$                                                                                                                                                                                                              |
| `a=*b` | $f(V)=V[\boldsymbol{a}\mapsto\bigcup_{\forall v\in\boldsymbol{b}}\boldsymbol{v}]$                                                                                                                                                                          |
| `*a=b` | $$f(V)=\left\{\begin{aligned}\forall v\in \boldsymbol{a},V[\boldsymbol{v}\mapsto\boldsymbol{v}\cup\boldsymbol{b}]&&\|\boldsymbol{a}\|>1\\ \forall v\in \boldsymbol{a},V[\boldsymbol{v}\mapsto\boldsymbol{b}]&& \|\boldsymbol{a}\|=1\end{aligned} \right.$$ |
最后一条是 Strong Update 的情况，即 $|\boldsymbol{a}|>1$
- 不清楚当前指向元素是否被修改，需要保留原来的值

当 $|\boldsymbol{a}|=1$，需要 Weak Update ，$f(V)=\forall v\in \boldsymbol{a},V[\boldsymbol{v}\mapsto\boldsymbol{b}]$

流敏感的指针分析算法很慢，实践中常采用稀疏分析

##### 堆上分配的内存
每个`malloc()`创建一个抽象地址

##### 结构体的指针分析
域非敏感 Field- Insensitive 分析
	把所有 struct 中的所有 fields当成一个对象

基于域的 Field-Based 分析
	把所有对象的特定域当成一个对象

域敏感 Field-sensitive 分析

| 赋值语句            | 转换函数                                                                      |
| --------------- | ------------------------------------------------------------------------- |
| `a=&(b->field)` | $\forall x\in \boldsymbol{b},\{x.field\}\subseteq\boldsymbol{a}$          |
| `a=b->field`    | $\forall x\in \boldsymbol{b},\boldsymbol{x.field}\subseteq\boldsymbol{a}$ |
| `a->field=b`    | $\forall x\in \boldsymbol{a},\boldsymbol{b}\subseteq\boldsymbol{x.field}$ |


##### 数组
数组粉碎：用一个抽象值描述数组中所有元素

数组扩展：对数组的每一维建立一个变量保存抽象值
	抽象域必须要推出下标（如区间），否则没有意义
	可只针对前 $k$ 个变量建立，可以加快分析速度，也可以处理数组大小未知的情况
	
数组分区：抽象为从索引区间到抽象值的映射

### 过程内优化
##### 基于CFL可达性的域敏感分析
```
FlowTo= new (assign | put[f] Alias get[f])* 
PointsTo = (rev_assign | rev_get[f] Alias rev_put[f])* rev_new 
Alias = PointsTo FlowTo
```

不能是
```
FlowTo = new FlowTo'
FlowTo' = put[f] FlowTo' get[f] | FlowTo' FlowTo'| assign | epsilon 
```
或
```
FlowTo= new (Alias | put[f] Alias get[f])* 
PointsTo = (Alias | rev_get[f] Alias rev_put[f])* new 
Alias = PointsTo FlowTo | assign | rev_assign
```

原因在于处理 assign 双向边和单向边的微妙之处

基于CFL和基于Anderson算法的域敏感分析是等价的

##### Steensgaard指向分析算法
	Unification-based
如果有可能需要将元素同时添加到两个集合中，则将两个集合合并

有两种合并： 
1. 有边可达的节点合并成同一个。 
	a. 即超集关系换成等价关系 
2. 被同一个指针指向的节点合并成同一个 
	a. 因为对该指针的读写会导致相关节点合并

总复杂度为 $O(n\alpha(n))$

### 过程间
不能做**精确**的**上下文敏感**的指针分析
- 上下文无关性是一个上下文无关属性 
- 域敏感性也是一个上下文无关属性 
- 两个上下文无关属性的交集不一定是上下文无关属性

降低上下文敏感性：把被调方法根据上下文克隆  $n$ 次
降低域敏感性：把域展开 $n$ 次

##### 降低域敏感性
转换成CFL可达性问题来进行精确的上下文敏感分析

对于约束 $\{a\}\subseteq\boldsymbol{p}$，化为方程 $\boldsymbol{p}=\boldsymbol{p}\cup\{a\}$

关于全称量词问题：需要在图上动态加边，通过降低域敏感性来去掉全称量词

主流框架中更多采用精确域敏感性，用克隆实现上下文敏感性的方 法

##### 函数指针分析
控制流分析和指针分析同时进行

确定函数调用目标的分析叫做控制流分析
	数据流分析在控制流图上完成，因此控制流分析是数据流分析的基础

##### Class Hierarchy Analysis 
根据i的类型确定 m可能的目标

优点：简单快速
缺点：非常不精确

##### Rapid Type Analysis
只考虑那些在程序中创建了的对象

可以有效过滤library中的大量 没有使用的类

三个集合 
- 程序中可能被调用的方法集合Methods，初始包括main 
- 程序中所有的方法调用和对应目标 Calls→Methods • 
- 程序中所有可能被使用的类Classe

Methods中每增加一个方法 
- 将该方法中所有创建的类型加到Classes 
- 将该方法中所有的调用加入到Call，目标初始为根据当前Classes集合类型匹配的方法 

Classes中每增加一个类 
- 针对每一次调用，如果类型匹配，把该类中对应的方法加入到Calls→Methods 
- 把方法加入到Methods当中

##### 精确的控制流分析 CFA 

CFA和指针分析需要一起完成 
- 指针分析确定调用对象 
- 调用对象确定新的指向关系

每个方法的参数和返回值都变成图上的点