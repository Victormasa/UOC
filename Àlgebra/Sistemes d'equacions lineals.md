### Discussió d'un SEL

**Teorema de Rouché-Fröbenius** 

Donat un sistema de m equacions lineals i n incògnites, es complex el següent:

- Si rg(A)=rg(M)=n, el sistema és un SCD (Sistema compatible determinat)
- Si rg(A)=rg(M)=r<n, el sistema ñes un SCI (sistema compatible indeterminat). En aquesta situació es diu que el sistema té ($n-r$) **graus de llibertat**
- Si rg(A)<rg(M), el sistema és un SI (Sistema incompatible)

On rg() es refereix al rang d'una matriu.

INSERT EXEMPLES

### Sistemes lineals homogenis

Es doi que un SEL és homogeni si tots els seus termes independents són zero, ñes a dir el ser és de la forma $$\begin{cases} a_{11}\cdot x_1+a_{12}\cdot x_2+\ldots+a_{1n}+x_n \\
a_{21}\cdot x_1+a_{22}\cdot x_2+\ldots+a_{2n}+x_n \\
\quad \ \ \vdots  \qquad \qquad \vdots \qquad \qquad \qquad \vdots \\
a_{1m}\cdot x_1+a_{m2}\cdot x_2+\ldots+a_{mn}\cdot x_n
\end{cases}$$
Matricialment, ho podem expressar de la seguent forma: $$A\cdot X = 0 $$
on $A$ és la matriu de coeficients, $X$ és el vector d'incògnites i $0=\begin{pmatrix} 0 \\ 0 \\ \vdots \\ 0 \end{pmatrix} \in \mathbb{R}^n$
Com podem veure la matriu ampliada, M, es forma afegint una columna de 0 a la matriu de coeficients, A, per la qual cosa tindrà que rg(M)=rg(A). Per tant, segons el teorema de Rouché-Fröbenius, es pot afirma que els SEL homogenis sempre seran compatibles. En concrtetm els SEL homogenis sempre accepten com a mínim l'anomenada **solució trivial**: $x=0\rightarrow x_1=x_2=\cdots=x_n=0$.

Per saber si un SEL homogeni té nomñes una única solució, (la trivial) o en té infinites, serà necessari esbrinar si rg(A)=$n$. En cas afirmatiu, es tractarà d'un SCD, on la única solució serà la trivial. En qualsevol altre cas, hi haurà infinites solucions, entre les quals es troba la tirvial.

INSERT EXEMPLE


### Resolució de SEL per Gauss

El mètode de Gauss consisteix en anar aplicant operacions especials sobre les files i columnes de la matriu de coeficiens ampliada, M, de manera que aquesta es transformi en una nova matriu, E, amb les següents característiques: 

- Les matrius E i M representen sistemes d'equacions equivalents.
- La matriu E està esglaonada inferiormens, és a dir de la forma:
				- INSERT FOTO

Les operacions especials que podem aplicar per a aconseguir matrius equivalents són:

- Transposar dues files
- Transposar dues columnes (s'ha de tenir en conte que també s'altera l'ordre de les variables en el SEL)
- Multiplicar una fila per a un escalar no nul
- Sumar una fila a una altra de multiplicada per un escalar (per extensió, sumar  a una fila una combinació lineal de les altres)
- Eliminar una **fila** de zeros

INSERT EXEMPLE


### Sistemes de Cramer. Resolució de SEL per Cramer

INSERT EXEMPLE

### Interpretació geomètrica dels SEL

- Si és un SCD, existeix un únic valor $(x_0,y_0)$ que és solució del sistema, $(x_0,y_0)$ pertany, simultàniament, a les m rectes, és a dir les m rectes es tallen en aquest punt
- Si és un SCI, totes les rectes tenen infinits punts en comú, per la qual cosa han de ser coincidents (es tracta de la mateixa tecta expressada de diferents formes). 
- Si és un SI, s'esdevincra que no hi ha cap punt en comú. Si m=2 es tractarà de dues recter paral·leles no coincidents.

A l'espai un pla $\pi$ és determinat per una equació lineal de tres incògnites (x,y,z):
$$\pi:ax+by+cz=d $$
Això significa que quan tenim un SEL format per $m$ equacions amb 3 incògnites, es pot interpretar com un conjunt de $m$ plans a l'espai. En aqueses condicions el teorema de Rouché-Fröbenius és una eina clau per a estudiar la posició relativa dels plans.


INSERT EXEMPLES VERIFICACIÓ i figura 3/9/10





