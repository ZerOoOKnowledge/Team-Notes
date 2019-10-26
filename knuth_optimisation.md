对于  $f_{l,r} = \min_{k=l}^{r-1}{f_{l,k}+f_{k+1,r}} + w(l,r)$ 如果满足
单调性: $\forall \ {l\leq l' \leq r' \leq r \quad w(l',r') \leq w(l,r)}$ 
四边形不等式: $\forall \ {l_1\leq l_2 \leq r_1 \leq r_2r \quad w(l_1,r_1)+w(l_2,r_2) \leq w(l_1,r_2) + w(l_2,r_1)}$ 
则 $f_{l, r}$ 满足四边形不等式且最优决策点 $m_{l,r}$ 单调, 即 $m_{l,r-1} \leq m_{l,r} \leq m_{l+1,r}$