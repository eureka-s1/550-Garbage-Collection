可满足性模理论 Satisfiability Modulo Theories：**给定一组理论**，根据给定逻辑，求在该组理论解释下公式的可满足性

#### EUF
Equality with Uninterpreted Functions

公理 
$a_i=b_i \Rightarrow f(a_1,\dots,a_n)=f(b_1,\dots,b_n)$
$a=b\Leftrightarrow \neg(a\not=b)$ 
等号的自反、对称和传递性

#### Eager 方法
将SMT问题编码成SAT问题：
- 引入符号替代函数调用，同时根据公理添加约束
- 引入布尔变量替代等式
- 根据自反性添加约束
- 同时为传递性添加约束

#### Lazy 方法
黑盒混合SAT求解器和各种理论求解器

理论求解器：
- 输入：属于特定理论的公式组，组内公式属于合取关系
- 输出：SAT 或者 UNSAT

给理论求解器添加接口函数
- `propagate`
	- 输入：
		- 属于当前理论的有限公式集合
		- 已知为真或为假的公式
	- 输出：**新推出的公式**和其**前提条件**
- `get_unsatisfiable_core`
	- 输入：一组公式，已知冲突
	- 输出：该公式（尽可能小的）子集，仍然冲突


DPLL(T)：理论求解器指导SAT搜索，效率有大幅提高
- 可以处理混合的多个理论，前提是不同理论的公式之间**没有共享变量**
- 解决方案：不同理论之间通过**接口属性**交换信息
	- **接口属性**：两种理论 $T_1$ 和 $T_2$ 都包含的命题集合
	- 通常无限多，无法遍历

#### Nelson-Oppen 方法
两个理论除了等号没有公共函数或谓词
理论具备 stably infinite 属性：即公理至少在某种**无限域**上成立
理论是凸包，即如果 $F\Rightarrow x_1=y_1\vee\cdots\vee x_n=y_n$，则有 $\exists i,F\Rightarrow x_i=y_i$

则接口属性只需要考虑变量之间的等价关系（此时**有限，可遍历**）

给理论求解器添加接口方法
- `infer_equalities`
	- 输入：一组公式 $F$，一组变量 $V$
	- 输出：对于$V$ 变量所有可以推出的等价关系


##### 非凸包
非凸包的情况只用另外考虑**等价关系的析取**：任何时候遇到一个等价关系的析取式，依次尝试每个等价关系，如果任意一个得出SAT，即整体SAT，如果全部UNSAT，即整体UNSAT

#### SMT Solver的使用
[Basic Commands | Online Z3 Guide](https://microsoft.github.io/z3guide/docs/logic/basiccommands)