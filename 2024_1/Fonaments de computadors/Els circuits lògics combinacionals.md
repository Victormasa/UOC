### Fonaments de l'electrònica digital
#### Circuits, senyals i funcions lògiques

**Circuit**: Sistema format per un cert nombre de senyals (cada una corresponent a un cable), un conjunt de dispositius electrònics que fan operacions sobre els senyals d'entrada, i que generen un cert nombre de senyals de sortida (0 o 1).

Prenem com a exemple un circuit amb una entrada, com ara el següent

![[Fotos/Screenshot 2024-10-27 at 08.02.06.png]]

Com que X només pot prendre dos valors 0 o 1, podem tenir quatre opcions disponibles:

- Un dispositiu que faci que la sortida sempre sigui 1
- Un dispositiu que faci que la sortida sempre sigui 0
- Un dispositiu que faci que la sortida valgui igual que l'entrada
- Un dispositiu que faci que la sortida valgui el contrari a l'entrada

Aixó ho podem resumir a la següent taula

Figura 1![[Fotos/Screenshot 2024-10-27 at 08.13.18.png]]

Prenem ara un circuit amb dues entrades (X i Y) com el següent

![[Fotos/Screenshot 2024-10-27 at 08.15.26.png]]

En aquest cas hi ha 16 possibles combinacions disponibles

Figura 2![[Fotos/Screenshot 2024-10-27 at 08.16.40.png]]

Veient els 2 exemples anteriors, obtenim la següent informació

- $g_1(x,y)$ val 1 només si valen 1 totes dues variables x i y simultàniament 
- $g_7(x,y)$ val 1 si x val 1 o bé y val 1 o bé valen 1 totes dues
- $f_2(x)$ val 1 només si x val 0

La funció g1 s'anomena AND (i), la funció g7 OR (o) i la funcio f2 NOT (no), provient de l'anglés totes. Així doncs els circuits lògics es construeixen a partir dels mateixos fonaments que la lògica.

#### Lògica de Boole

Una àlgebra de Boole és una entitat matemàtica formada per un conjunt que te dos elements, unes operacións bàsiques sobre aquests elements i una llista d'axiomes defineixen les propietats que compleixen les operacions.

Els dos elements de l'àlgebra es poden anomenar cert i fals, o més comunment 0 i 1. Així, una variable booleana  variable lògica pot prendre els valors 0 i 1. 

Les operacions booleanes bàsiques són:

- Negació o comlementació o NOT
	- Correspon a la partícula no i es representa amb una cometa simple ('). Així, l'expressió X' denota la negació de la variable X, i es llegeix "*no X*"
- Producte lògic o AND
	- Correspon a la conjunció *i* de la lògica i es representa amb símbol "*·*". Així si *X* i *Y* són variables lògiques, l'expressió *x·y* denota el seu producte lògic, i es llegeix "X i Y"
- Suma lògica o OR
	- Correspon a la conjunció *o* de la lògica i es representa amb símbol "*+*". Així, l'expressió   "*x+y*" denota la suma lògica de les variables, i es llegeix "X o Y"

Aquests resultats els podem escriure a una taula de la següent forma, a la dreta de kla línea tenim totes les combinacions possibles i a l'esquerre el resultat

![[Fotos/Screenshot 2024-10-27 at 12.25.51.png]]

Els axiomes que descriuen el comportament de les operacions booleanes són els següents:

1. La propetat commutatva
$$
\displaylines{
x + y = y + x \\
x · y = y · x
}
$$
2.  La propietat associativa

$$
\displaylines
{x + (y + z) = (x + y) + z \\ x · (y · z) = (x · y) · z}
$$
3. La propietet distributiva

$$
\displaylines {x · (y + z) = x · y + x · z \\ x + (y · z) = (x + y) · (x + z)}
$$

4. Els elements neutres

$$
\displaylines {x + 0 = x \\ x · 1 = x}
$$

5. La complementació


$$
\displaylines {x + x' = 1 \\ x · x' = 0}
$$
A partir d'aquests axiomes, es poden demostrar una sèrie de lleis o teoremes molt útils per a treballar amb expressions algebraiques booleanes. 

###### **Teoremes de l'àlgebra de Boole** 

1. Principi de dualitat
	- Tota identitat deduïda a partir dels axiomes conitnua essen certa si les operacion + i · i els element 0 i 1 s'intercanvien en tota la expressió (demostrable amb les propietats anteriors)
2. Llei d'idempotència
$$ \displaylines {x + x = x \\ x · x = x } $$

3. Llei d'absorció
 $$\displaylines {x + x · y = x \\ x · (x +y) = x }$$
4. Llei de dominància
$$ \displaylines {x +1 = 1 \\ x · 0 = 0} $$

5. Llei d'involució
$$ (x')' = x $$
6. Lleis de Morgan
$$ \displaylines {(x + y)' = x' · y' \\(x · y)' = x' + y'} $$
En les expressions algebraiques, utiitzem els parèntesis de la mateixa manera que hi estem acostumats a fer-ho en aritmètica entera; per exemple, l'expressió *x + y · z* és el mateix que la *x + (y · z)* i és diferent que *(x + y) · z*.

Per a negar una expressió sencera la posarem entre parèntesis, i per tant, *x + y'* és diferent de *(x + y)'*.


#### Representacions de funcions lògiques

##### Expressions algebraiques
Les expressions algebraiques estan formades per variables lògiques, els elements 0 i 1 els operadors producte (·), suma (+) i negació ('), i els símbols (,) i =. 

MItjançant aquests elements es pot expressar qualsevol funció lògica. Per exemple, la funció g4 de la figura 2 es pot expressar així::

$$g4(x,y)=x' · y$$
L'expressió *x' · y* val 1 (´s certa) només si valen 1 (són certes) les subexpressions x' i y simultàniament. L'expressió *x'* val 1 només si x val 0. En la descrició de la funció g4 es pot comprovar que només val 1 si *x = 0 i y = 1*.

Una mateixa funció lògica es pot expressar mitjançant infinites expressions algebraiques equivalents. 

Per saber si dues expressions algebraiques són equivalet, és a dir expressen la mateixa funció, podem analitzar si una es pot derivar de l'altre usant els axiomes i leis de l'àlgebra de Boole. Per exemple, la primera llei de Morgan ens diu que les funcions lògiques f i g són la mateiza:
$$ f(x,y) = (x+y)' ;;;;;; g(x,y)=x'·y'$$
A la inversa, a partir de l'expressió algebraica una funció podem trobar altres expressions aplicant els axiomes i les lleis de l'algebra de Boole. Per exemple si tenim la següent funció
$$ f(x,y,z)= x · y' · z + x' · y · z + x · y · z$$
I ara apliquem l'axioma 3 (propietat distributiva), obteniom l'expressió equivalen següent:
$$f(x, y, z) = x · y’· z + (x’ + x) · y · z$$
Per l'axioma 5 (de complementació) i després el 4 (element neutre), obtenim el que expressem a continuació:
$$f(x, y, z) = x · y’ · z + 1 · y · z = x · y ’· z + y · z$$
##### Taules de la veritat

Una taula de la veritat expressa una funció lògica especificant el valor que te la funció per a cada possible combinació de valors de les variables d'entrada.

A la columna de més a la dreta escriurem el resultat de la funció amb el valor corresponent de cada variable. De la següent forma.

![[Fotos/Screenshot 2024-10-28 at 07.20.58.png]]

Podem expressar el comportament de diverses funcions que tenen les mateixes variables d'entrada en una única taula de veritat. En aquest cas a la dreta de la línea vertical, hi haurà tantes columnes com funcions. En aquest cas no cla establir cap convenció per l'ordre de les columnes. Ho expressarem de la següent manera

![[Fotos/Screenshot 2024-10-30 at 17.27.50.png]]

##### Correspondència entre expressions algebraiques i taules de veritat

És important saber passar una expressió algebraica d'una funció a la seva taula de veritat, i viceversa.

Per a obtenir la taula de veritat a partir d'una expressió algebraica, podem fer-ho de dues maneres:

- Avaluar l'expressió per a cada combinació de les variables i escriure al lloc corresponent de la taula el resultat de l'avaluació. 
	- Tenim la següent funció:$$f(a,b,c)= a + a'b'c+ac'$$
	- Si avaluem l'expressió per al cas de la combinació [0 0 0], obtenim el següent resultat:$$0+1·1·1+0·0=0+1+0$$
	- Per tant, en segona fila hi anirà un 1. I així succesivament fins a haver avaluat la funció per a totes les combinacions.
- Analitzar l'expressió a cista, deduir per quins valors de les variables la funció val 1 o 0, i omplir la taula.
	- Donada la següent funció:$$f(a,b,c)= a + a'b'c+ac'$$
	- Veiem que la funció sempre val 1 quan la variable a=1 (per la llei de dominància). Per tant, podem posar un 1 en totes les files en les quals a=1.
	- A continuació, estudiem els casos en què a=0. L'expressió de la funció ens queda de la manera següent. $$f(0,b,c)= 0 + 0'·b'c+0·c'=b'c$$
	- Aquesta expressió cal 1 només en el cas [b c] = [0 1]. Per tant posarem un 1 en la fila corresponent a la combinació [0 0 1]. Per la resta de combinacions que ens queden per omplir la funció val 0.

Observem qu ele pas d'expressió a la taula de veritat ens pot ser molt útil a l'hora de determinar si dues expressions algebraiques són equivalents o no ho són. Podem obtenir la taula de la veritat a partir de cadascuna de les expressions, i si les taules resultants són iguals podem concloure que les dues expressions corresponen a una mateixa funció.

##### Expressions en suma de mintermes

Ja hem vist que hi ha infinites expressions algebraiques equivalents per a una funció qualsevol. Ara bé, quaslevol funció lògica es pot expressar amb una expressio en duma de productes. És a dir, una expressió de la forma següent: $$A+B+C$$
On *A, B i C* són termes producte, és a dir, tenen la forma que reproduïm a continuació: $$Z·Y·Z$$
on *X, Y i Z* són variables lògies, bé negades o bé sense negar. Per exemple, les dues ecpressions següent sorresponen a la mateixa funció, però només la segona té la forma de suma de productes:
$$ 
\begin{aligned}
f(x,y,z)=(x+yz')'z \\ 
f(x,y,z)=x'y'z+x'yz 
\end{aligned}
$$

A partir de la taula de la veritat d'una funció, és molt senzill d'obtenir-ne una exxpressió en suma de productes. Vegem les taules de veritat de les quatre funcions següents:

![[Fotos/Screenshot 2024-11-01 at 11.14.20.png]]

Si examinem $f_0, f_1 i f_2$,  veiem que tenen la particularitat de valer 1 només per a una de les combinacions de les variables d'entrada, de manera que les podem expressar fàcilment amb un sol terme producte, en el qual apareixen totes les variables, negades o sense negar. Les variables que valen 0 en la combinació que fa que la funció valgui 1 apareixeran negades en el terme del producte següents per a les funcions anteriors.
$$ 
\begin{aligned}
f(x_2,x_1,x_0)=x_2'x_1'x_0 \\ 
f(x_2,x_1,x_0)=x_2x_1'x_0' \\
f(x_2,x_1,x_0)=x_2x_1x_0'
\end{aligned}
$$
S'anomena terme mínim o minterme el terme producte (únic) que expressa una funció que només val 1 per a una sola combinació de les variables d'entrada.

No és tan senzill d'obtenir "a vista" una expressió per a la funció $F$, ja que val 1 per a diverses combinacions de les variables. Ara bé, sí que podem veure fàcilment que F val 1 si $f_0$ o bé $f_1$ o bé $f_2$ valen 1. És a dir,
$$ F=f_0+f_1+f_2 $$
Per tant obtenim el següent $F(x_2,x_1,x_0)=x_2'x_1'x_0+x_2x_1'x_0'+x_2x_1x_0'$ que és una expressió algebraica de $F$ en forma de suma de productes. 

Així, doncs, a partir de la taula de veritat d'una funció podem obtenir una expressió en suma de productes fent la suma lògica dels mintermes que la formen. Per això, l'expressió que obtenim d'aquesta manera s'anomena suma de mintermes. 
##### Altres funcions comunes

###### Funció O-exclusica o XOR

Aquesta funció val 1 quan alguna de les dues vatiables d'entrada val 1, però no quan valen 1 totes dues alhora; per aixó rep el nom d'*O-exclusiva*. És la funció $g_6$ de la figura 2.

Es representa amb símbol $\oplus$, i té aquesta taula de veritat: 

| $a$ | $b$ | $a\oplus b$ |
| --- | --- | ----------- |
| 0   | 0   | 0           |
| 0   | 1   | 1           |
| 1   | 0   | 1           |
| 1   | 1   | 0           |
$a\oplus b=a'b+ab'$

La funció XOR de més de dues variables es calcula així:
$$a\oplus b \oplus c \oplus d = (((a\oplus b)\oplus c)\oplus d)$$
Per tant, dóna 0 si un nombre parell de les variables val 1, i dóna 1 si un nombre senar de les variables val 1. Fixem-nos que en el cas de dues variables, aquest fet es tradueix en el següent: 

- $a \oplus b = 0 => a, b$ tenen els mateixos valors
- $a \oplus b = 0 => a, b$ tenen valors diferents

Per tant la funció XOR ens permet saber si dues variables són iguals o no ho són. 

###### Funció NAND

És la negació de l'AND, és a dir $a$ NAND $b$ $= (a·b)'$.

Per tant, val 1 sempre que no es compleixi que les dues variables d'entrada valen 1, És dons la funció $g_{14}$ de la figura 2. Aquesta és la seva taula de la veritat:

| a   | b   | (a·b)' |
| --- | --- | ------ |
| 0   | 0   | 1      |
| 0   | 1   | 1      |
| 1   | 0   | 1      |
| 1   | 1   | 0      |

###### Funció NOR

És la negació de l'OR, és a dir  $a$ NAND $b$ $= (a+b)'$.

Per tant, val 1 només quan vap de les dues variables d'entrada val 1. És la funció $g_8$ de la figura 2. Aquesta és la seva taula de veritat

| a   | b   | (a+b)' |
| --- | --- | ------ |
| 0   | 0   | 1      |
| 0   | 1   | 0      |
| 1   | 0   | 0      |
| 1   | 1   | 0      |

##### Funcions especificades incompletament

Hi ha funcions per a les quals algunes combinacions de les variables d'entrada no es produiran mai. Per exemple, suposem una funció $f(x_2,x_1,x_0)$ en la qual les variables corresponen a senyals connectats a tres aparells de mesura del so en una sala de manera que tenim el següent:

- $x_2 =$ 1 si el so supera 100 dB, $x_2 =$ 0 altrament,
- $x_1 =$ 1 si el so supera 200 dB, $x_1 =$ 0 altrament,
- $x_0 =$ 1 si el so supera 200 dB, $x_0 =$ 0 altrament

La combinació  {$x_2$ $x_1$ $x_0$} = {0 1 0} no es produirà mai, ja que és impossible que el so estigui per sota dels 100 dB i per sobre dels 200 dB simultàniament. Tampoc no hi haurà mai les combinacions [0 0 1], [0 1 1] i [1 0 1].

Les combinacions que no es produiran mai es diuen combinacions no importa o combinacions don't care. 

En l ataula de veritat d'una funció, escriurem x en les files corresponents a les combinacions no importa. Per ecemple suposem que la funció anterior ha de valer 1 si el so està entre (100 dB, 200 dB] o si el so supera els 300 dB. La seva taula de veritat és la següent:

| $x_2$ | $x_1$ | $x_0$ | $f$ |
| ----- | ----- | ----- | --- |
| 0     | 0     | 0     | 0   |
| 0     | 0     | 1     | x   |
| 0     | 1     | 0     | x   |
| 0     | 1     | 1     | x   |
| 1     | 0     | 0     | 1   |
| 1     | 0     | 1     | x   |
| 1     | 1     | 0     | 0   |
| 1     | 1     | 1     | 1   |
## Implementació de circuits lògics combinacionals

### Portes lògiques. Síntesi i anàlisi


