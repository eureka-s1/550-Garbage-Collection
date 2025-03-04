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
