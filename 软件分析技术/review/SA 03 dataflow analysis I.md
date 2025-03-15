数据流分析的收敛性：
- 该算法保证终止 Terminating 
- 该算法一定合流 Confluent
- 终止+合流=收敛 Convergence

[[#示例：符号分析]]

[[#可达定值分析]]
[[#可用表达式分析]]
[[#活跃变量分析]]
[[#繁忙表达式分析]]
![[v2-04b8cf9b176e6e7e63dde16bf12f7ed3_720w.webp]]

### 示例：符号分析
[[slides03_dataflow_analysis_I.pdf#page=2|slides]]
引入 $\gamma$ 表示抽象值对应的集合
	$\gamma(正)=\{x\in\mathbb{Z}|x>0\}$

$\alpha$ 将具体域的值映射到抽象域

运算操作 $\oplus,\ominus,\otimes$ 分别定义为抽象域上的 $+,-,\times$

分支：定义合并操作$$\sqcup(v_1,v_2)=\left\{ \begin{aligned} v_1 &&v_1=v_2\\
槑&&\text{otherwise}\end{aligned}\right.$$循环：引入抽象值 $\perp$ ，$\gamma(\perp)=\varnothing,x \sqcup \perp=x$，初始结点上的抽象值都为 $\perp$ ，表示没有对应具体状态，输入节点为输入的抽象值，其他节点的抽象值都为空，每次选择一个节点更新，如果值有变化，该节点的后继节点也需要加入待更新集合，反复迭代直到没有节点需要更新
##### 算法
令$\mathbf{S}=\{(s_x,s_y,s_z)|s_x,s_y,s_z\in\{\text{正,负,零,槑},\perp \}\}$

每个节点的值为$\mathbf{S}$的一个元素，代表对应语句执行之后的抽象状态，用OUT 表示
	同时用IN表示语句执行之前的抽象状态 

初始值 
	$OUT_{entry}=(负,零,正)$ 
	$OUT_{其他结点}=(\perp,\perp,\perp)$  

节点转换函数 $f_v:\mathbf{S}\rightarrow\mathbf{S}$
	$f_{exit}=id$
	$f_{其他节点}=根据相应语句进行计算$

合并运算$IN_v=\sqcup_{w\in pred(v)}OUT_w$
节点更新运算$OUT_v = f_v(IN_v)$ 

如果某个节点的**前驱节点**发生了变化，则使用节点更新运算更新该节点的附加值 

如果没有任何节点的值发生变化，则程序终止

```
OUT_entey = I
for v in (V-entry): OUT_v = T//初值

ToVisit = succ(entry)
While (ToVisit.size > 0) {
	v in ToVisit
	ToVisit -= v
	for w in pred(v): IN_v ∪= OUT_w
	if (OUT_v != f_v(IN_v)) ToVisit ∪= succ(v)
	OUT_v = f_v(IN_v)
}
```

##### 正确性分析
因为计算到收敛，所以分析结束的时候下面这些等式必然成立，$v\not=entry$$$\begin{aligned}IN_v&=\bigsqcup_{w\in pred(v)}DATA_w\\
OUT_v&=f_v(IN_v)\end{aligned}$$如果分析正常结束，给定输入抽象值对应的任意具体输入，程序执行到任意节点的状态一定包含在该节点的抽象值中

### 数据流分析小结
采用四套近似方案处理程序 
- 近似方案1：抽象状态代表程序的多个具体状态
- 近似方案2：针对控制流节点编写转换函数
- 近似方案3：在控制流路径分叉时，复制抽象状 态到所有分支 
- 近似方案4：在控制流路径合并时，用$\sqcup$操作合并多个抽象状态 

四种近似方案也代表着数据流分析的四种不精确 性来源

不精确：
 - 近似方案1：发生在需要将具体值集合映射到抽象值时
 - 近似方案2：转换函数无法精确给出结果时
 - 近似方案3：每个具体状态只能到达一个分支，形成不精确
 - 近似方案4：合并的状态可能会引入 不精确值

设计数据流分析
 - 近似方案1：设计抽象域，对应的$\alpha,\gamma$函数和初始值
 - 近似方案2：设计从基本语句导出转换函数的方法
 - 近似方案3：设计从条件导出压缩函数的方法
 - 近似方案4：设计$\sqcup$操作

### 可达定值分析
[[slides03_dataflow_analysis_I.pdf#page=39|slides]]
对程序中任意语句，分析运行该语句后每个变量的值可能是由哪些语句赋值的，给出语句标号。要求**上近似**，即返回值**包括**所有可能的定值。

##### 算法
抽象域：从变量到语句标号集合的映射

初始值：所有变量都映射到空集（未定值）

抽象值含义：具体执行序列集合，定值语句落在对应范围内

合并：对应集合的并

节点转换函数：
$f_v(甲)(x)=(甲(x)-KILL_v^x)\cup GEN_v^x$ 
- 对于赋值语句 x=
	- $KILL_v^x=\{所有赋值给x的语句编号\}$
	- $GEN_v^x=\{当前语句编号\}$
- 对于其他语句
	- - $KILL_v^x=GEN_v^x=\{\}$

$f(甲)=(甲-KILL)\cup GEN$  又叫数据流分析的**标准型**

```
//数据流分析的标准代码
OUT_entey = I
for v in (V - entry): OUT_v = T//初值

ToVisit = V - entry // 为什么
While (ToVisit.size > 0) {
	v in ToVisit  // 任意
	ToVisit -= v
	IN_v = ⊔ for w in pred(v) OUT_w
	if (OUT_v != f_v(IN_v)) ToVisit ∪= succ(v)
	OUT_v = f_v(IN_v)
}
```

如果某个初始值在更新过程中没有被改变，后续节点也不会被更新

符号分析不存在这个问题，因为初始值不变意味着对应节点是死代码 

可达定值分析也可以改成这种方式
- 方式一：一开始就假设所有变量被entry定 值
- 方式二：设置特殊的抽象值作为初值

##### 小结
和符号分析的关键不同点
	抽象值对应具体执行序列的集合
	在分析开头加入所有其他节点到ToVisit

由于更通用，标准数据流分析也按照以上两种情况定义

### 可用表达式分析
[[slides03_dataflow_analysis_I.pdf#page=57|slides]]
给定程序中某个位置p，如果从入口到p的所有路径都对表达式exp求值，并且最后一次求值后该表达式的所有变量都没有被修改，则exp称作p 的一个可用表达式。
	**下近似**

##### 算法
抽象值：表达式的集合 

初始值：程序中表达式的**全集**

抽象值含义：对应从头到当前位置的具体执行序列的集合，其中可用表达式是当前位置抽象值的**超集** 

合并：集合交

节点转换函数：
$f_v(甲)=(甲-KILL_v)\cup GEN_v$ 
- 对于赋值语句 x=
	- $KILL_v^x=\{所有包含x的表达式\}$
	- $GEN_v^x=\{当前求值语句中不含x的表达式\}$
- 对于其他语句
	- $KILL_v^x=\{\}$
	- $GEN_v^x=\{当前语句中求值的表达式\}$

##### 小结
和之前的分析不同 
- 分析是下近似，即抽象域包含的为具体域的子集 
- 初始值为全集 
- 合并操作为求交

标准数据流框架同时提供对上近似和下近似的支持

### 活跃变量分析
[[slides03_dataflow_analysis_I.pdf#page=68|slides]]
**活跃变量**：给定程序中的某条语句s和变量v，如果在s执行前保存在v中的值在后续执行中还可能被读取就被称作活跃变量
	**上近似**

##### 算法
抽象值：变量的集合

初始值：空集

抽象值含义：对应从当前位置开始的**任意长度**的具体执行序列的集合
	因为程序有可能会无限执行，不能定义为到exit结束的序列

合并：集合并

节点转换函数：
$f_v(甲)=(甲\backslash KILL_v)\cup GEN_v$ 
- $KILL_v=\left\{\begin{aligned}\{x\} && v:=\:x=exp\\ \{x\} &&v:= \:int \:x\\\{\} && otherwise  \end{aligned}\right.$
- $GEN_v=v 中读取的所有变量$

```
IN_exit = I
for v in (V - exit): IN_v = T//初值

ToVisit = V - exit // 如果引入特殊的初值，加入所有节点
While (ToVisit.size > 0) {
	v in ToVisit  // 任意
	ToVisit -= v
	OUT_v = ⊔ for w in succ(v) IN_w
	if (IN_v != f_v(OUT_v)) ToVisit ∪= pred(v)
	IN_v = f_v(OUT_v)
}
```
##### 小结
和之前的分析不同 
- 分析是反向开始
- 程序有可能不结束，也就是说执行序列不一定到达 exit
	- 和之前执行序列一定从entry开始不同
	- 需要一开始将所有exit之外节点加入toVisit
	- 数据流框架只在结束的序列上讨论正确性

### 繁忙表达式分析
[[slides03_dataflow_analysis_I.pdf#page=78|slides]]
**繁忙表达式**：从执行某个程序节点**之前**开始，在其中变量被修改之前，在所有终止执行中一定会被读取的表达式
- 如果从某个程序点开始的所有执行都不终止，则可返回任意结果
- **下近似**

##### 算法
抽象值：表达式的集合 
初始值：程序中表达式的**全集**
抽象值含义：对应从当前位置开始的**任意长度**的具体执行序列的集合，其中可用表达式是当前位置抽象值的**超集** 

合并：集合交，$OUT_v=\sqcap_{w\in succ(v)}IN_w$
	正确性：甲乙所包含的任意具体执行过程均读取的表达式包括在 $(甲\sqcap 乙)$ 中

节点转换函数：
$f_v(甲)=(甲-KILL_v)\cup GEN_v$ 
- 对于赋值语句 x = exp
	- $KILL_v^x=\{所有包含x的表达式\}$
	- $GEN_v^x=\{当前求值语句中的表达式\}$
- 对于其他语句
	- $KILL_v^x=\{\}$
	- $GEN_v^x=\{当前语句中求值的表达式\}$
```
IN_exit = I
for v in (V - exit): IN_v = set of all exprs//初值

ToVisit = V - exit 
While (ToVisit.size > 0) {
	v in ToVisit  // 任意
	ToVisit -= v
	OUT_v = ⊓ for w in succ(v) IN_w
	if (IN_v != f_v(OUT_v)) ToVisit ∪= pred(v)
	IN_v = f_v(OUT_v)
}
```

正确性：给定任意长度的具体执行序列，以开始位置看， 在该序列上的可用表达式都在开始位置的抽象值中

证明：如果执行序列不终止，返回任意结果，只讨论结束的序列。从序列的结束位置开始反向对长度做归纳。合并操作的正确性主要来自于集合交保证了繁忙表达式的性质，即一定会被读取。而对于每个节点，如果是赋值语句 `x= exp` 那么包含 $x$ 的表达式都会被删除，因为被修改，而其他表达式都会被加入。