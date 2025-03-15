##### 抽象解释
具体化函数 $\gamma$ 将抽象值映射为具体值
抽象化函数 $\alpha$ 将具体值映射为抽象值
假设抽象域上存在偏序关系 $\sqsubseteq$

##### 伽罗瓦连接  Galois Connection 
我们称 $\gamma$ 和 $\alpha$ 构成抽象域 $\boldsymbol{虚}$ 和具体域 $\mathbf{D}$ 之间的一个伽罗瓦连接，记为$$(\mathbf{D},\subseteq)\leftrightharpoons^{\gamma}_{\alpha}(\boldsymbol{虚},\sqsubseteq)$$当且仅当$$\forall X\in \mathbf{D},甲\in \boldsymbol{虚}:\alpha(X)\sqsubseteq甲\iff X\subseteq \gamma(甲)$$
$(\mathbf{D},\subseteq)\leftrightharpoons^{\gamma}_{\alpha}(\boldsymbol{虚},\sqsubseteq)$ 当且仅当以下所有公式成立
- $\alpha$ 是单调的：$\forall X,Y\in\mathbf{D}:X\subseteq Y\Rightarrow \alpha(X)\sqsubseteq \alpha(Y)$
- $\gamma$ 是单调的：$\forall 甲,乙\in \boldsymbol{虚}:甲\sqsubseteq乙\Rightarrow\gamma(甲)\subseteq\gamma(乙)$
- $\gamma\circ\alpha$ 保持或增大输入：$\forall X\in \mathbf{D}:X\subseteq\gamma(\alpha(X))$
- $\alpha\circ\gamma$ 保持或缩小输入：$\forall 甲\in \boldsymbol{虚}:\alpha(\gamma(甲))\sqsubseteq甲$

给定 $\mathbf{D}$ 上的函数 $f$  和 $\boldsymbol{虚}$ 上的函数 $\text{子}$ 

$子$ 是 $f$ 的安全抽象 $\iff$  $(\alpha\circ f\circ\gamma)(甲)\sqsubseteq子(甲)$ $\Rightarrow$ $(f\circ \gamma)(甲)\subseteq(\gamma\circ 子)(甲)$
$子$ 是 $f$ 的最佳抽象 $\iff$  $\alpha\circ f\circ\gamma=子$
$子$ 是 $f$ 的精确抽象 $\iff$  $f\circ\gamma=\gamma\circ子$

最佳抽象总是存在，但精确抽象不一定存在

### 程序分析的安全性
执行踪迹（具体执行序列）：(语句编号,内存状态)构成的序列
程序分析：分析程序所有执行踪迹集合的属性
程序分析的安全性：在分析结果域存在某种偏序关系，与理想结果相同或者更大视为安全

程序的执行踪迹集合和分析结果域构成伽罗瓦连接
- 具体域：执行踪迹集合 + 集合子集关系
- 抽象域：分析结果 + 分析结果上的偏序关系
- $\alpha$：踪迹集合对应的精确分析结果，定义为
	-  $\alpha(X)=\sqcup_{x\in X}\beta(x)$
- $\gamma(甲)=\{x|\beta(x)\sqsubseteq甲\}$

其中，抽象域，$\beta$ 函数（单条踪迹的分析）需要特定分析定义

数据流分析在每个程序点产生一个结果，可以看做是下面多个伽罗瓦连接的复合![[51768c2e-33b9-4d8d-985e-e8195b4d94ae.png|350]](从下至上）

#### 迹语义 Trace Semantics
迹语义是一个函数，将程序和输入集合映射为执行踪迹的集合![[c86b6a26-a1f7-4f1e-b9da-be76f248c46b.png|350]]

#### 控制流图的具体语义
假设每个控制流节点$v$对应两个函数：
- 具体（内存状态）转换函数 $trans_v:M\to 2^M$
- 控制转移函数 $next_v:M\to 2^{succ(v)}$

以上函数的返回值都是集合，对应不确定的执行，比如返回随机数

考虑反向分析的话，需要反向执行程序，程序的反向执行通常也是不确定的

定义如下单步执行函数，即每次把序列加长一步$$\begin{aligned}
Step(T)=&\{t + (v',m')|\\
&t\in\\
&v'\in next_{last(t).node}(last(t).mem),\\
&m'\in trans_{v'}(last(t).mem)\} \cup T\\
\end{aligned}$$一个程序的迹语义定义为 $Step^{\infty}(T)=\lim_{n\to\infty}Step^n(T)$

任意结点 $v$ 上的抽象域转换函数 $f_v$ 满足如下条件$$t\in Step(\gamma(甲))\wedge last(t).node=v\Rightarrow t\in \gamma(f_v(甲))$$即轮询函数$F$是$Step$的安全抽象，$Step(\gamma(甲))\subseteq \gamma(F(甲))$

#### 小结
程序的具体语义：
- 反复应用某种具体单步执行函数得到程序的踪迹集合
程序的抽象语义：
- 针对问题设计抽象域
- 设计抽象单步执行函数，是具体执行函数的安全抽象
- 证明抽象单步执行函数收敛
	- 通常基于单调性+半格高度有限

### 程序分析的分类-敏感性

xx敏感性：有没有考虑xx

一般而言，抽象过程中考虑的信息越多，程序分析的精度就越高，但分析的速度就越慢
- 流敏感性flow-sensitivity 
	- 流非敏感分析（flow-insensitive analysis）：如果把程序中语句随意交换位置（即：改变控制流），如果分析结果始终不变，则该分析为流非敏感分析。
	- 流敏感分析（flow-sensitive analysis）：其他情况
	- 数据流分析通常为流敏感的
- 路径敏感性path-sensitivity 
	- 路径非敏感分析：假设所有分支都可达，忽略分支循环语句中的条件
	- 路径敏感分析：考虑程序中的路径可行性，尽量只分析可能的路径
	- 带条件压缩函数的分析就是路径敏感分析
- 上下文敏感性context-sensitivity 
- 字段敏感性field-sensitivity
