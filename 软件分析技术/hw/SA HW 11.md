2300012969 盛梓航
##### 1. SSA 
为了防止被编译器直接优化，需要在代码中加一点条件判断
```c
int foo(int a, int b, int c, int *i) {
    a = c;
    if( b ){
        c = c + b;
        b = b + 1;
        b = a + b;
        i = &a;
    }
    *i = 10;
    return a;
}
```
在这段代码中，变量 $a$ 是 address-taken 的，所以无法完全转换成SSA，由于 $i$ 可能存放了 $a$ 的地址，所以除了开头对于 $a$ 的赋值，$*i$ 也有可能对 $a$ 所在内存位置赋值

这段代码中还能看到正常的 top-level 变量，如 $b,c$ 相关的语句，结果都是存在寄存器，优化成 SSA 的
```
c = c + b;
b = b + 1;

%8 = add nsw i32 %2, %1
%9 = add nsw i32 %1, 1
```
而关于 $a$ 的语句还是要借助 `alloca` / `load` / `store` 这样借助内存存储局部变量
```
define dso_local i32 @foo(i32 noundef %0, i32 noundef %1, i32 noundef %2, ptr noundef %3) #0 {
  %5 = alloca i32, align 4
  store i32 %0, ptr %5, align 4
  store i32 %2, ptr %5, align 4
  %6 = icmp ne i32 %1, 0
  br i1 %6, label %7, label %12

7:                                                ; preds = %4
  %8 = add nsw i32 %2, %1
  %9 = add nsw i32 %1, 1
  %10 = load i32, ptr %5, align 4
  %11 = add nsw i32 %10, %9
  br label %12

12:                                               ; preds = %7, %4
  %.0 = phi ptr [ %5, %7 ], [ %3, %4 ]
  store i32 10, ptr %.0, align 4
  %13 = load i32, ptr %5, align 4
  ret i32 %13
}
```


##### 2. relational abstraction
```
var i:int, j:int;
begin
  i = 0;
  j = 0;
  while (i<=10) do
    i = i + 1;
    j = j + 2;
  done;
end
```

**区间抽象精度**：
- $x\in[11,11]$
- $y\in[0,+\infty]$

![[Pasted image 20241118135841.png]]

**八边形抽象精度**：
- $x\in[11,11]$
- $y\in[11,+\infty]$

![[Pasted image 20241118135950.png]]

**convex polyhedra抽象精度**：
- $x\in[11,11]$
- $y\in[22,22]$

![[Pasted image 20241118140230.png]]

最理想的结果精度能直接预测出 $x,y$ 的值，
而八边形抽象中 $x,y$ 的线性关系不含系数，并不能发现过程中恒有 $2x=y$ ，而只能看出 $y\geqslant x$ ，
区间抽象并不能发现 $x,y$ 的关系，只能预测出 $y\leqslant 0$
