Joint Entropy, Conditional Entropy, Mutual Information and KL-Divergence(Relative Entropy)

#### Joint Entropy

> **Definition:** Given r.v. $X$, $Y$, joint prob distribution $P_{XY}=(p_{ij})_{m\times n}$.
$$
H(X,Y)=\sum_{i,j}p_{ij}\log_2\frac{1}{p_{ij}}(\text{bits})
$$

$$
H(X,Y)\le H(X)+H(Y)
$$
When $X$, $Y$ are independent, $H(X,Y)=H(X)+H(Y)$; when $X=Y$(dependent), $H(X,Y)=H(X)=H(Y)$.

#### Conditional Entropy

$$
H(Y|X=x_i)=\sum_{j=1}^n p(Y=y_j|X=x_i)\cdot\log_2\frac{1}{p(Y=y_j|X=x_i)}(\text{bits})
$$
> **Definition:** (Conditional Entropy)
$$
H(Y|X)=\sum_{i=1}^m p(X=x_i)\cdot H(Y|X=x_i)
$$

When $X$, $Y$ are independent, $H(Y|X)=H(Y)$; when $X=Y$(dependent), $H(X,Y)=0$.

$$
H(X,Y)=H(Y|X)+H(X)=H(X|Y)+H(Y)
$$

 **Lemma:**  $H(Y)\geqslant H(Y|X),H(X)\geqslant H(X|Y)$ 

#### Mutual Information
>**Definition:** $I(X;Y)=H(X)+H(Y)-H(X,Y)$


Use venn diagram to show the relations between $I(X,Y),H(X),H(Y),H(X,Y),H(X|Y),H(Y|X)$
![[Pasted image 20250315163000.png|450]]
#### KL-Divergence
$r.v. \:X$，ture pmf is $P=(p_1,p_2,\cdots,p_n)$(unkown)，
estimation $Q=(q_1,q_2,\cdots,q_n)$，encode length $\log\frac{1}{q_1},\cdots,\log\frac{1}{q_n}$

>Definition: $D(P||Q)=\sum_{i}p_i\log\frac{p_i}{q_i}$


Note: $I(x;y) = D(p(x,y)||p(x)p(y))$

> **Lemma:** $\forall a_1,\cdots,a_n,b_1,\cdots,b_n>0$ $$\sum_{i}a_i\log\frac{a_i}{b_i}\geqslant\Big(\sum_{i}a_i\Big)\log\frac{\sum_{j}a_j}{\sum_{j}b_j}$$

convex/concave
(1) Fix Q in P$$\begin{aligned}
\lambda D(P_1||Q)+(1-\lambda)D(P_2||Q)&=\sum_{i}\lambda p_{1i}\log\frac{p_{1i}}{q_i}+(1-\lambda) p_{2i}\log\frac{p_{2i}}{q_i}\\
&=\sum_{i}\lambda p_{1i}\log\frac{\lambda p_{1i}}{\lambda q_i}+(1-\lambda) p_{2i}\log\frac{(1-\lambda) p_{2i}}{(1-\lambda) q_i}\\
&\geqslant \sum_{i}(\lambda p_{1i}+(1-\lambda) p_{2i})\log\frac{\lambda p_{1i}+(1-\lambda) p_{2i}}{\lambda q_i+(1-\lambda) q_i}\\
&=D(\lambda P_1+(1-\lambda) P_2||Q)
\end{aligned}
$$convex

(2)(3) similar to case 1 