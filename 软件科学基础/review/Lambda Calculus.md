![[Pasted image 20250305012740.png]]

语法：
```lambda
t ::= x      
	| λx.t
	| t t
```
语义：
Alpha-Renaming：绑定的变量可以随意改名
Beta-Reduction：即函数调用，也是唯一的计算步骤


一般 $\lambda a.\lambda b.$ 可以和 $\lambda ab.$ 在用法上互换

##### Church Boolean
$T=\lambda t.\lambda f.\:t$
$F=\lambda t.\lambda f.\:f$

定义一个 $\mathrm{IF}=\lambda b.\lambda t.\lambda f.  \:b\:t \: f$，相当于 $b$ 为 True 返回 $t$，否则返回 $f$
现在可以来定义基本逻辑运算：
- $\mathrm{AND}=\lambda ab.\mathrm{IF}\:a\:b\:F$
- $\mathrm{OR}=\lambda ab.\mathrm{IF}\:a\:T\:b$
- $\mathrm{NOT}=\lambda a.\mathrm{IF}\:a\:T\:F$

##### Church Numerals
用[Church数](https://link.zhihu.com/?target=https%3A//en.wikipedia.org/wiki/Church_encoding)来对数字编码，对于任意数$n=\lambda f.\:f^n$ ，所以有
- $0=\lambda f.\lambda x.\:x$
- $1=\lambda f.\lambda x.\:f(x)$
- $2=\lambda f.\lambda x.\:f(f(x))$
- $3=\lambda f.\lambda x.\:f(f(f(x)))$

定义整数上的基本运算：
- $\mathrm{SUCC}=\lambda n.\lambda f.\lambda x.\:f\:(n\:f)\: x$
- $\mathrm{ADD}=\lambda n.\lambda m.\lambda f.\lambda x.\:n\:f\:(m\:f\:x)$
- $\mathrm{MUL}=\lambda n.\lambda m.\lambda f.\lambda x.\:n\:(m\:f)\:x$
- $\mathrm{EXP}=\lambda n.\lambda m.\lambda f.\lambda x.\:n\:m\:f\:x$

注意这里的 $\mathrm{EXP}$ 是 $m^n$ ，而且完全没必要这么定义，比如
- $\mathrm{ADD}=\lambda n.\lambda m.\:n\:\mathrm{S}\:m$
- $\mathrm{MUL}=\lambda n.\lambda m.\:n\:(\mathrm{ADD}\: m)\:0$
这么写主要是展示细微不同带来的巨大差距，以及上述两条语义的强大能力


##### Y Combinator
递归：
$\mathrm{Y}=\lambda f.\:(\lambda x.\: f\:(x\:x))\:(\lambda x.\: f\:(x\:x))$

$\mathrm{Y}\:f=f\:(\mathrm{Y}\:f)$


