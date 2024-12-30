#### Equacions d'una recta al pla              

###### Equació vectorial

Donats dos punts de pas de $r$, $P:(P_1,P_2)$, es pot considerar el vector director $v=\overrightarrow{PQ}=(v_1.v_2)=(q_1-p_!,q_2-p_2$. Qualsevol altre punt $X:(x,y)$ de la recta $r$ verificarà l'equació:$$X=P+k·v, \quad\text{on}\quad k \in \mathbb{R}$$
##### Equacions paramètriqus

L'equaciçó anterior es pt reescriure de la següent manera: $$(x,y)=(p_1,p_2)+k·(v_1,v_2)$$
és a dir $$(x,y)=(p_1+k\cdot v_1,p_2+k·v_2)$$
Expressió equivalent al següent sistema:

$$\begin{cases}
x=p_1+k·v_1 \\
y=p_2+k·v_2
\end{cases}\quad k \in \mathbb{R} 
$$ 
##### Equació contínua

Aïllant el paràmetre $k$ al sistema anterior obtenim es equacions continues de $r$ (sempre que $v_1,v_2\neq0 \text{ i } v_1\neq v_2$) $$\begin{cases}
x=p_1+k·v_1 \\
y=p_2+k·v_2
\end{cases} \iff
\begin{cases}
k=\frac{x-p_1}{v_1} \\
k=\frac{y-p_2}{v_2}
\end{cases}
$$
I per tant, $$ \frac{x-p_1}{v_1}=\frac{y-p_2}{v_2}$$
##### Equació punt-pendent i equació explícita

Aïllant la $y$ de l'expressió anterior s'arriba a:

1. L'equació punt-pendent: $y-p_2=\frac{v_2}{v_1}(x-p_1)$, és a dir: $$ y-p_2 = m\cdot x-p_1$$
on m és el **pendent** de $r$
2. L'equació explicíta: $y=m\cdot(x-p_1)+p_2=m\cdot x-m\cdot p_1+p_2$, és a dir: $$y=m\cdot x+n$$
siguent $n=-m\cdot p_1+p_2$ l'ordenada d'origen.


##### Equació general

També és possible desenvolupar l'expressió anterior de la següent manera $$\frac{x-p_1}{v_1}=\frac{y-p_2}{v_2}\leftrightarrow v_2\cdot(x-p_1)=v_1\cdot(y-p_2)\leftrightarrow v_2\cdot x-v_1\cdot y-v2\cdot p_1+v_1\cdot p_2=0$$
De manera genèrica:
$$ Ax+By+C=0$$
on $A=v_2,B=-v_1 \text{ i }C=-v_1\cdot p_1+v_1\cdot p_2$

#### Productes i ortogonalitat

##### Producte escalar, mòdul d'un vector i angle entre vectors

Donat dos vectors a l'espai vectorial $\mathbb{R}^n$, $u=(u_1,u_2,...,u_n), v=(V_1,v_2,...,v_n)$ es defineix el producte escalar de tots dos vector $u\cdot v$   de la manera següent: $$ u \cdot v = u_1\cdot v_1+ u_2\cdot v_2\cdot u_2+...+u_n\cdot v_n$$ El mòdul o longitud d'un vector $v=(v_1,v_2,...,v_n)$ és $$\|v\| = \sqrt{v\cdot v}=\sqrt{v_1^2+v_2^2+...+v_n^2}$$
Un vector unitari és aquell vector que el seu mòdul val 1. Donat un vector no nul $u$ de $\mathbb{R}^n$, sempre és possible obtenir un altre vector $v$ unitari amb la mateixa direcció i sentit que $u$; per a això tan sols cal prendre $\|v\|=\frac{u}{\|u\|}$. Aquest procés s'anomena normalització del vector $u$. 

Donats $u \text{ i } v$, dos vectors de $\mathbb{R}^n$, es defineix la distància entre tots dos com a: $$d(u,v)=\|u - v\|$$
A $\mathbb{R}^2 \text{ i } \mathbb{R}^3$ es pot definir l'angle entre dos vectors no nuls utilitzant el producte escalar:

Donats dos vectors $u$ i $v$, dos vectors no nuls de $\mathbb{R}^2 \text{ o } \mathbb{R}^3$ es defineix l'angle entre tots dos com el nombre real $\cos{\theta}=\frac{u\cdot v}{\|u\cdot\|v\|}$ (NOTA: $cos\theta$ es calcula en radiants)

#### Vectors i bases ortogonals a $\mathbb{R}^n$

Donats $u\text{ i } v \in\mathbb{R}^n$, dos vectors a $\mathbb{R}^n$, es diu que són ortogonals (intuïtivament perpendiculars) entre ells quan es compleix $u\cdot v=0$ 

El conjunt de tots els vectors $u\in\mathbb{R}^n$ que són ortogonals al subespai $W$ s'anomena complement ortogonal a de $W$ i es denota $W^{\perp}$ 

Sigui $W$ un subespai vectorial de $\mathbb{R}^n \text{ i } B={u_1,...,u_k}$ una base de $W$. Es diu que $B$ és una base ortogonal de $W$ su els vectors que la componen són ortogonals entre ells. $$u_i\cdot u_j = 0 \ \forall \ i\neq j$$
D'altre banda, es diu que $B$ és una base ortonormal de $W$ su és una base ortogonal i, a més, tots els vectors que la componen són unitaris. 

IMPORTANT: Donada una base ortogonal $B$ serà inmediat obtenir una base ortonormal. N'hi ha prou de normalitzar cada un dels vectors de $B$, és a dir $v_i=\frac{u_i}{\|u_i\|}$ on $i$ és la posició del vector 1,2,3..., $u$ els vectors de la base $B$ i $v4$ el vector resultant.