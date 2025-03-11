# Lecture 3 Joint Entropy, Conditional Entropy, Mutual Information and KL-Divergence(Relative Entropy)

## Joint Entropy

Given r.v. $X$, $Y$, joint prob distribution $P_{XY}=(p_{ij})_{m\times n}$.
$$
H(X,Y)=\sum_{i,j}p_{ij}\log_2\frac{1}{p_{ij}}(\text{bits})
$$
$$
H(X,Y)\le H(X)+H(Y)
$$
When $X$, $Y$ are independent, $H(X,Y)=H(X)+H(Y)$; when $X=Y$(dependent), $H(X,Y)=H(X)=H(Y)$.

## Conditional Entropy

$$
H(Y|X=x_i)=\sum_{j=1}^n p(Y=y_j|X=x_i)\cdot\log_2\frac{1}{p(Y=y_j|X=x_i)}(\text{bits})
$$
**Def.** (Conditional Entropy)
$$
H(Y|X)=\sum_{i=1}^m p(X=x_i)\cdot H(Y|X=x_i)
$$
When $X$, $Y$ are independent, $H(Y|X)=H(Y)$; when $X=Y$(dependent), $H(X,Y)=0$.

$$
H(X,Y)=H(Y|X)+H(X)=H(X|Y)+H(Y)
$$

**Contidioning reduces entropy**
$$
\begin{align}
&H(X,Y)=H(X|Y)+H(Y),H(X,Y)\le H(X)+H(Y)\\
&\Rightarrow H(X)\ge H(X|Y)\\
\end{align}
$$

## Mutual Information

$$
\begin{align}
&H(X)-H(X|Y)\\
=&H(Y)-H(Y|X)\\
=&H(X)+H(Y)-H(X,Y)
\end{align}
$$

**Def.** (Mutual Information) r.v. $X,Y$, define their mutual information as
$$
\begin{align}
I(X;Y)=&H(X)-H(X|Y)\\
=&H(Y)-H(Y|X)\\
=&H(X)+H(Y)-H(X,Y)
\end{align}
$$
$$
I(X;Y)=\sum_{i,j}P(X=x_i,Y=y_j)\log\frac{P(X=x_i,Y=y_j)}{P(X=x_i)P(Y=y_j)}
$$

We can define **Joint Entropy**, **Conditional Entropy**, and **Mutual Information** for r.v. $X_1,X_1,\cdots,X_n,Y_1,\cdots,Y_n$ similarly and natually.
$$
H(X_1,\cdots,X_n)=H(X_1)+H(X_2|X_1)+H(X_3|X_1X_2)+\cdots+H(X_n|X_1\cdots X_{n-1})
$$

## Kullback-Leibler Divergence(KL-divergence)/ Relative Entropy

**Def.** (KL-divergence/ Relative Entropy)
For pmf $P=(p_1,\cdots,p_n),Q=(q_1,\cdots,q_n)$,
$$
KL(P||Q)=\sum_i p_i\log_2\frac{p_i}{q_i}
$$
(Relative entropy is sometimes more useful in real cases.)

Mutual information is the KL-divergence of the joint distribution and the multiply of marginal distribution of $X,Y$, thus it is non-negative.
