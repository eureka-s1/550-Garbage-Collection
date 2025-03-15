·100012969 盛梓航
```
x-=1;
y+=1;
while(y<z) {
	x*=-100;
	y+=1;
}
```

输入：$x$ 为负，$y$ 为零， $z$ 为正

初始状态
```datalog
out(x, entry, 负)
out(y, entry, 零)
out(z, entry, 正)
```
边关系
```datalog
edge(entry, 1)
edge(1, 2)
edge(2, 3)
edge(3, exit)
edge(3, 4)
edge(4, 5)
edge(5, 3)
```
**第一条语句**
转换语句
```datalog
out(x, 1, 正) :- in(x, 1, 正)
out(x, 1, 零) :- in(x, 1, 正)
out(x, 1, 负) :- in(x, 1, 负)
out(x, 1, 负) :- in(x, 1, 零)
```
合并（用甲表示某个抽象状态，$v$ 表示 $x,y,z$ ）
```datalog
in(v, 1, 甲) :- edge(entry, 1), out(v, entry, 甲)
```

**第二条语句**
转换语句
```datalog
out(y, 2, 正) :- in(y, 2, 正)
out(y, 2, 负) :- in(y, 2, 负)
out(y, 2, 零) :- in(y, 2, 负)
out(y, 2, 正) :- in(y, 2, 零)
```
合并
```
in(v, 2, 甲) :- edge(1, 2), out(v, 1, 甲)
```

**第三条语句**
转换语句
```datalog
out(v, 3, 甲) :- in(v, 3, 甲)
```
合并
```datalog
in(v, 3, 甲) :- edge(2, 3), out(v, 2, 甲)
in(v, 3, 甲) :- edge(5, 3), out(v, 5, 甲)
```

**第四条语句**
转换语句
```datalog
out(x, 4, 负) :- in(x, 4, 正)
out(x, 4, 零) :- in(x, 4, 零)
out(x, 4, 正) :- in(x, 4, 负)
```
合并
```datalog
in(v, 4, 甲) :- edge(3, 4), out(v, 3, 甲)
```

**第五条语句**
转换语句
```datalog
out(y, 5, 正) :- in(y, 5, 正)
out(y, 5, 负) :- in(y, 5, 负)
out(y, 5, 零) :- in(y, 5, 负)
out(y, 5, 正) :- in(y, 5, 零)
```
合并
```datalog
in(v, 5, 甲) :- edge(4, 5), out(v, 4, 甲)
```

出口
```datalog
in(v, exit, 甲) :- edge(3, exit), out(v, 3, 甲)
out(v, exit, 甲) :- in(v, exit, 甲)
```

输出的结果应该为
```
out(x ,exit, 正)
out(x ,exit, 负)
out(y ,exit, 正)
out(z ,exit, 正)
```
#### 分析精度
相比之前的符号分析，精度提高了。具体来说，实际上用抽象状态的集合代替了槑。例如，输入 $x$ 为正， 第一条语句 `x-=1` 令 $x$ 的抽象状态为零和正，而不是槑。再比如题目中的输入，如果是符号分析，负$\sqcup$正会返回槑，而这里会同时返回正、负



