## 05.562 · Fonaments de Computadors · 2023-24  
## PAC2 - Segona prova d'avaluació continuada  

Cognoms: Martinez Santos
Nom: Víctor

Format i data de lliurament  
- Per a dubtes i aclariments sobre l’enunciat, adreceu-vos al consultor responsable de la vostra aula. 
- Cal lliurar la solució en un fitxer PDF fent servir una de les plantilles lliurades conjuntament amb aquest enunciat.
- S’ha de lliurar a través de l’aplicació de Lliurament i registre d’AC de l’apartat Avaluació de la vostra aula. 
- La data límit de lliurament és el 6 de novembre (a les 24 hores).  
- Raoneu la resposta en tots els exercicis. Les respostes sense justificació no rebran puntuació.  
### Respostes

**Exerici 1**: donada la taula de veritat següent


| $a$ | $b$ | $c$ | $d$ | $f$ | P   |
| --- | --- | --- | --- | --- | --- |
| 0   | 0   | 0   | 0   | 1   | 0   |
| 0   | 0   | 0   | 1   | 1   | 1   |
| 0   | 0   | 1   | 0   | 0   | 2   |
| 0   | 0   | 1   | 1   | 0   | 3   |
| 0   | 1   | 0   | 0   | 1   | 4   |
| 0   | 1   | 0   | 1   | 0   | 5   |
| 0   | 1   | 1   | 0   | 1   | 6   |
| 0   | 1   | 1   | 1   | 0   | 7   |
| 1   | 0   | 0   | 0   | 1   | 8   |
| 1   | 0   | 0   | 1   | 1   | 9   |
| 1   | 0   | 1   | 0   | 0   | 10  |
| 1   | 0   | 1   | 1   | 0   | 11  |
| 1   | 1   | 0   | 0   | 1   | 12  |
| 1   | 1   | 0   | 1   | 0   | 13  |
| 1   | 1   | 1   | 0   | 1   | 14  |
| 1   | 1   | 1   | 1   | 0   | 15  |
1.  Expresseu la funció $f$ com a suma de mintermes

Donada la taula de veritat i analitzant els seus resultats, per obtenir la funció com a suma de mintermes ens fixarem en tots els casos en que la sortida sigui 1. Per tant, tindrem el següent

$$
\displaylines {f=P_0+P_1+P_4+P_6+P_8+P_{12}+P_{14} \\ f=a'b'c'd'+a'b'c'd+a'bc'd'+ab'c'd'+ab'c'd+abc'd}
$$
La funció expressada en mintermes és $f=a'b'c'd'+a'b'c'd+a'bc'd'+ab'c'd'+ab'c'd+abc'd$.

2. Simplifiqueu a funció f fent servir les propietats i les lleis de l'àlgebra de Boole.
Per poder simplificar la següent funció, utilitzarem diverses propietats després d'agrupar els termes per simiituds, de la següent manera:  $f=a'b'c'd'+a'b'c'd+a'bc'd'+ab'c'd'+ab'c'd+abc'd$ -> $f=(a'b'c'd'+a'b'c'd)+(a'bc'd')+(ab'c'd'+ab'c'd)+(abc'd)$. Un cop fet aixó fem una primera simplifació. Pel primer conjunt de termes veiem que es repeteixen tres valor i ho podem escriure de la següent manera $a'b'c'(d'+d)=a'b'c'1$. A través de la complementació (axioma e) sabem que una variable més la mateixa negada és igual a 1.  En aquest cas, el segon terme no pot ser simplificat més. Pel següent conjunt de nombres que podem simplificar veiem que es tornen a repetir tres variables i ho podem escriure de la següent manera $ab'c'(d'+d)=ab'c'1$, un altre cop a través de l'axioma e (la complementació) podem simplificar la funció. Ara procedim a comprovar si la funció es pot simplificar més o no, recordem que ara tenim $f=a'b'c'+a'bc'd'+ab'c'+abc'd$, com veiem hi ha dos termes que poden ser simpificats. Així que repetint els mateixos pasos previs juntem els termes que poden ser simplificats, en aquest cas: $f=(a'b'c'+ab'c')+a'bc'd'+abc'd$ podem simplificar-ho un altre cop fent el mateix mèotde d'abans $a'b'c'+ab'c'=(a'+a)b'c'->1·b'c'$, el que ens queda el següent, $f=a'bc'd'+b'c'+abc'd$. El que ens ha deixat amb la funció en el seu estat més simplificat. 
$$f=a'bc'd'+b'c'+abc'd$$

3. Completeu el següent cronograma


![[Captura de pantalla 2024-11-06 a les 14.28.24.png]]


**Exercici 2**: Donada la taula de la veritat següent:

| $a$ | $b$ | $c$ | $d$ | $g$ |
| --- | --- | --- | --- | --- |
| 0   | 0   | 0   | 0   | X   |
| 0   | 0   | 0   | 1   | 0   |
| 0   | 0   | 1   | 0   | 1   |
| 0   | 0   | 1   | 1   | X   |
| 0   | 1   | 0   | 0   | X   |
| 0   | 1   | 0   | 1   | 0   |
| 0   | 1   | 1   | 0   | 1   |
| 0   | 1   | 1   | 1   | X   |
| 1   | 0   | 0   | 0   | X   |
| 1   | 0   | 0   | 1   | 0   |
| 1   | 0   | 1   | 0   | 1   |
| 1   | 0   | 1   | 1   | 0   |
| 1   | 1   | 0   | 0   | 1   |
| 1   | 1   | 0   | 1   | X   |
| 1   | 1   | 1   | 0   | X   |
| 1   | 1   | 1   | 1   | 1   |

1. Minimitzeu a dos nivells la funció $g$ mitjançant el mètode de Karnaugh, i implementeu el resultat amb portes lògiques a dos nivells.


El primer pas per poder dur a terme el mètode de Karnaugh, el primer pas serà reescriure la taula de veritat, el que ens quedarà una cosa així

| $cd/ab$ | $ab$ |     |     |     |
| ------- | ---- | --- | --- | --- |
| $cd$    | 00   | 10  | 11  | 01  |
| 00      | X    | X   | 1   | X   |
| 10      | 0    | 0   | X   | 0   |
| 11      | X    | X   | 1   | 0   |
| 01      | 1    | 1   | X   | 1   |

Un cop tenim la taula reescrita, agruparem els termes segons el seu resultat, per exemple agruparem els 1 en paquets de 1, 2, 4 o altres equivalents a potències de 2. En aquest cas al ser una funció especificada incompletament ens imaginarem que les x valen 1 per facilitat, ja que les x són casos que mai succeiran.

![[Captura de pantalla 2024-11-06 a les 17.02.29.png]]



Bé un cop ho tenim agrupat procedirem a agafar els dos paquets que tenim i mirarem els elements. Començant pel vermell, ens fixarem en tots aquells elements que no varien en la funció, en aquest cas, la $d$ llavors tenim que no varia i el seu valor es 0 així que demoment sabem $g=d'$. Per altre banda, el paquet de taronja, els únics valor que no canvien són $a$ i $b$ llavors la funció que tindrem serà: $g=d'+ab$. 

A continuació l'esquema de portes lògiquesl

![[Captura de pantalla 2024-11-06 a les 16.38.18.png]]

2. Sintetitzeu la funció g amb un descodificador 3-8 i les portes lògiques addicionals que creieu necessàries
Bé primer mirarem quina de les 4 variables deixarem fora del decodificador, en aquest cas la d, ja que el decodificador no pot tenir més de 3 entrades i podem fer-ne us d'ella desde fora. Un cop tenim quina serà la variable que influirà desde fora, mirarem quins són els casos en els que a,b,c donen 1 a la taula de la veritat sense tenir en compte d, per tal de poder configurar el decodificador. Un cop sabem quines son les sortides que ens interessen del decodificador configurarem cada sortida per que validi que d te el valor que ha de tenir, si és 0 la negarem del contrari la conectarem directament a la porta. 

Un cop hem fet tot aixó, connectarem totes les sortides de les portes and a una porta or, que comprovarà si algun dels casos anteriors es compleix per poder donar una sortida vàlida.

![[Captura de pantalla 2024-11-06 a les 20.22.04.png]]


**Exercici 3**: Considereu l’existència del següent bloc combinacional MULT22 que multiplica dos  nombres naturals de 2 bits cadascun d’ells i dona el resultat en 4 bits. El rang dels nombres d’entrada A i B és [0..3] i la sortida P és dins el rang [0..9].  
Es demana que:

1. Dissenyeu el circuit MULT22 amb una memòria ROM de mida 24 per 4  
bits. Indiqueu el contingut de la memòria ROM en binari.

El primer que farem serà configurar dues sortides, que aniran connectades a la memòria ROM que ens donarà el resultat de la sortida. La ROM la configurarem de la següent forma (4 bits de direcció i 4 bits de dades), aixó ens permetrà emmagatzemar 16 vàlors que seràn la multiplicació dels 2 nombres en binari. 

![[Captura de pantalla 2024-11-06 a les 23.17.30.png]]

2. Dissenyeu el circuit MULT22 a partir de memòries ROM de mida 23 per 4 bits i les portes i blocs addicionals que considereu necessàries. Indiqueu en binari el contingut de cada una de les memòries ROM utilitzades






