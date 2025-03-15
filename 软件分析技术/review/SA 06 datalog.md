Datalog——逻辑编程语言Prolog的子集
一个Datalog程序由如下规则组成：
- predicate1(Var or constant list) :- predicate2(Var or constant list),predicate3(Var or constant list), … 
- predicate(constant list)

Datalog程序的语义
- 反复应用规则，直到推出所有的结论——即不动点算法

#### 逻辑编程角度看程序分析
一个Datalog编写的正向数据流分析标准型，假设并集
```Datalog
out(D, V):- gen(D, V)
out(D, V):- edge(V', V), out(D, V'), not_kill(D, V)
out(d, entry) // if d in I
```
交集
```Datalog
out(D, V):- gen(D, V)
out(D, v):- out(D, v1), out(D, v2),..., out(D, vn), not_kill(D, v)
out(d, entry) // if d in I
```

not_kill 关系的构造效率较低，但是，引入 not 可能带来矛盾
- p(x) :- not p(x)
- 不动点角度理解：单次迭代并非一个单调函数

解决方法：分层(stratified)规则 
- 谓词上的任何环状依赖不能包含否定规则

2005年，斯坦福Monica Lam团队开发了高效 Datalog解释器bddbddb，使得Datalog执行效率接近专门算法的执行效率 (datalab checker?)

