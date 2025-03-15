2300012969 盛梓航

半格：指针变量到地址集合的映射
交汇：对应地址集合取并

| 赋值语句   | 转换函数                                                                                        |
| ------ | ------------------------------------------------------------------------------------------- |
| `a=&b` | $f(V)=V[\boldsymbol{a}\mapsto\{b\}]$                                                        |
| `a=b`  | $f(V)=V[\boldsymbol{a}\mapsto\boldsymbol{b}]$                                               |
| `a=*b` | $f(V)=V[\boldsymbol{a}\mapsto\bigcup_{\forall v\in\boldsymbol{b}}\boldsymbol{v}]$           |
| `*a=b` | $f(V)=\forall v\in \boldsymbol{a},V[\boldsymbol{v}\mapsto\boldsymbol{v}\cup\boldsymbol{b}]$ |

对于前两种语句，明显可以写成数据流 GEN/KILL 标准型，所以满足分配性

对于第三条语句，只需要说明 $$\big(\bigcup_{\forall v\in\boldsymbol{b_1},\boldsymbol{b_1}\in V_1}\boldsymbol{v}\big)\:\cup\big(\bigcup_{\forall v\in\boldsymbol{b_2},\boldsymbol{b_2}\in V_2}\boldsymbol{v}\big)=\big(\bigcup_{\forall v\in\boldsymbol{b_1}\cup\boldsymbol{b_2}}\boldsymbol{v}\big)$$这是成立的，所以满足分配性

而对于第四条语句，当 $|\boldsymbol{a}|=1$，需要 Weak Update ，$f(V)=\forall v\in \boldsymbol{a},V[\boldsymbol{v}\mapsto\boldsymbol{b}]$

所以对应地址集合取并可能会改变集合的大小，进而改变更新的方式（原来的值是否保留），所以不满足分配性，只满足 $f(V_1)\cup f(V_2)\subseteq f(V_1\cup V_2)$
