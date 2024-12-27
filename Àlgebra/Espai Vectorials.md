#### Vectors a l'espai

Donat un sistema de coordenades rectangular en el pla sabem que un punt P està determinat per un parell ordenat $(p_1,p_2)$ pertanyent a $R^2$ com el conjunt de punts del pla.

Donat dos punts $P$ i $Q$ al pla $\mathbb{R}^2$, es defineix el vector $v=\overrightarrow{PQ}$ com el segment orientat que té origen a $P$ i final a $Q$. El vector $v$ té com a components o coordenades $v=\overrightarrow{PQ} = (q_1-p_1,q_2-p_2)$.

![[Fig1.png]]

#### Combinació lineal. Subespai generat

Sigui $(V,+,·)$ un espai vectorial real, es diu que un vector $v \in V$ és una **combinació lineal** del vectors $u_1,u_2,...,u_n \in V$ si existeixen $k_1,k_1,...,k_n$ nombres reals tal que: $$v=k_1·u_1+k_"·u_2+...+k_n·u_n$$
![[Exemple1.png]]



Sigui $(V,+,·)$ un espai vectorial real i $\{u_1,u_2,...,u_n\}$ un conjunt de vectors $V$. S'anomena **espai vectorial generat per $\{u_1,u_2,...,u_n\}$** al subespai vectorial de $V$ format per totes les combinacions lineals que es poden formar amb els vectors $\{u_1,u_2,...,u_n\}$ tal que: $$<\;u_1,u_2,...,u_n\;> = \{k_1·u_1+k_"·u_2+...+k_n·u_n |k_i \in \mathbb{R} \; \forall_i = 1,2,...,n\}$$
El conjunt $\{u_1,u_2,...,u_n\}$ constitueix un sistema generador de l'espai vectorial $<\;u_1,u_2,...,u_n\;>$

![[Exemple6.png]]
#### Dependència i independència lineal. Base i dimensió d'un espai vectorial

Donat un espai vectorial i un conjunt de vectors, es diu que aquests són linealment dependents si n'hi ha un d'ells que es pot expressar com a combinació lineal de la resta. En cas contrari, els vectors linealment independents. 

Sigui $(V,+,·)$ un espai vectorial real i $\{u_1,u_2,...,u_n\}$ un conjunt de vectors $V$. Els vectors $u_1,u_2,...,u_n$ són linealment dependents si existeix algun $i \in \{1,2,...,n\}$ tal que $u_i$ es pot expressar com a combinació lineal de la resta de vectors. Tal que $$u_i=k_1·u_1+...+k_{i-1}·u_{i-1}+k_{i+1}·u_{i+1}+...+k_n·u_n$$
![[Exemple7.png]]

Es defineix el rang d'un conjunt de vectors com el nombre màxim de vectors d'aquest conjunt linealment independents. 

![[Exemple11.png]]

Sigui $(V,+,·)$ un espai vectorial real i $B=\{u_1,u_2,...,u_n\}$ un conjunt de vectors de $V$ tal que: 

1. $B$ és sistema generador de $V$
2. $B$ está format per vectors linealment independents

En aquest cas, es diu que $B$ és una **base** de $V$, i que la **dimensió de $V$** és $n\;(dim(V)=n)$.

![[Exemple13.png]]

A $\mathbb{R}^n$, el conjunt de $n$ vectors: $$B={(1,0,...,0),(0,1,....,0),...,(0,0,...,1)}$$ és una base especial anomenada **base canònica**.
Tambés se sol usar la notació $e_1=(1,0,...,0),e_2(0,1,...,0),...,e_n=(0,0,...,1)$ 

Sigui $(V,+,·)$ un espai vectorial real de dimensió $n$.

1. Tot sistema generador de $V$ estarà compost per un mínim de $n$ vectors.
2. Tot conjunt linealment independent $V$ estarà compost per un màxim de $n$ vectors
3. $n$ vectors linealment independents constitueixen una base
4. Un sistema generador de $V$ format $n$vectors és una base

#### Coordenades d'un vector en una base

El concepte de base d'un espai vectorial $V$ permet definir un sistema de coordenades de $V$. La clau per a poder definir-lo és el següent teorema de representació única d'un vector en una base:

**TEOREMA** 

Sigui $B=\{u_1,...,u_n\}$ una base de l'espai vectoriall real $V$. Es demostra que per a cada vector $v \in V$ hi ha un únic conjunt de nombres reals tals que $$v=c_1·u_1+...+c_n·u_n$$ on $c_1,...,c_n$ s'anomena **coordenades de $v$ en la base $B$**.

![[Exemple15.png]]

#### Dimensió d'un subespai

La definició de base d'un espai vectorial es generalitza a subespais:

Sigui $W$ un subespai d'un espai vectorial $V$. Un conjunt de vectors $W$, $B=\{u_1,...,u_n\}$ és una base del subespai $W$ si i només si:

1. $B$ és un sistema generador de $W$
2. $B$ és un conjunt linealment independent

S'animena **dimensió del subespai $W$ (dim($W$))** al nombre de vectors d'una base.
