2300012969 盛梓航

SMT Solver：Z3
Theory：
1. **等式（Equality）**
2. **算术（Arithmetic）**：包括某系线性算术、非线性算术等。
3. **数组（Arrays）**
4. **位向量（Bit-vectors）**
5. **浮点数（Floating points）**
6. **代数数据（Algebraic Datatypes）**：代数数据类型的理论被编译成未解释函数。在这个理论中，构造函数是注入函数，通过添加部分逆元的公理来确保注入性。
7. **字符串、正则表达式和序列理论（Strings, Regular Expressions, and Sequences）**
8. **基数和伪布尔不等式（Cardinality and Pseudo-Boolean inequalities）**
9. **外部理论（External Theories）**：Z3允许通过用户理论插件来扩展其理论支持

无法求解的约束：（来自 Non-linear arithmetic 部分自带的例子）
![[Pasted image 20241209213920.png]]
运行结果
![[Pasted image 20241209214313.png]]
无法的求解的原因是：非线性整数算术问题是**不可判定**的，这意味着不存在一个程序，对于所有输入都能正确地终止，并给出 SAT 或 UNSAT 的答案。部分情况下，Z3 可能可以在非线性问题上给出答案；某些情况下，Z3可能会返回 unknown，表示它不能确定公式是否可满足；还有一些情况，它可能会陷入无限循环