抽象部分结束，接下来是搜索部分

关键：约束求解技术

#### 约束求解

**合取范式**

优化：
1. 冲突检测
2. 赋值推导
3. 预处理：归结Resolution，Pure literal elimination，Equivalence classes
4. 变量选择：基于子句集的/基于历史的
5. 冲突导向的子句学习 CDCL Conflict-Driven Clause Learning

标准推导方法
1. 单元传播 Unit Propagation
2. Unate Propagation



高效单元传播检测：每个子句设置两个指针，指向两个未赋值的文字，如果赋值让其中一个变为假了，就顺序寻找下一个未赋值的文字，如果找不到，就可以单元传播

新的变量选择方法VSIDS：Variable State Independent Decaying Sum
- 首先按变量出现次数给所有变量打分
- 添加新子句的时候给子句中的变量加分
- 每隔一段时间把所有变量的分数除以一个常量

#### DPLL

##### 选择切割
唯一蕴含点Unique Implication Point：最后一次 赋值到冲突的所有路径都要经过的节点

切割距离冲突最近的唯一蕴含点的后继所有通往冲突路径的汇入边