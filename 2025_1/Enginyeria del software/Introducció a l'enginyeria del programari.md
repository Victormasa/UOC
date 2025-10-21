### Organització de l'enginyeria del programari

L'IEEE defineix un mètode dient que "descriu les característiques del procés o procediment disciplinat utilitzat en l'enginyeria del producte o en la prestació d'un servei"

#### Organització del desenvolupament, operació i manteniment

Les activitats d'operació acostumen a ser contínues, mentre que el desenvolupament acostuma a ser temporal el desenvolupament té un inici clar i un final definit per l'èxit o fracàs.

Les tasques d'operació tendeixen a ser repetitives, mentre que el desenvolupament proporciona un resultat únic.

Mentres que el desenvolupament s'acostuma a organitzar pen forma de projectes, l'operació s'organitza d'acord amb serveis. 

El manteniment es pot organitzar de manera contínua, sobretot en el cas del manteniment correctiu, o bé de manera temporal, com és el del maneniment evoltiu.

#### Organització dels projectes de desnvolupament

S''han anat deifinint diferents mètodes per al desenvolupament de programari. La descripció d'un procés inclou:

- Les tasques i l'ordre en que s'han de dur a terme
- Els rols que tindran les diferents persones que participen en el desenvolupament, així com a les responsabilitats i les tasques que han de fer
- Quins artefactes s'utilitzaran (documentació, programes, ...) 

#### Activitats de l'enginyeria de programari 

Els mètodes defineixen quines tasques es duran a terme en cada procés. Tot i que cada mètode te les seves particularitats. 

El terme activitat fa referència a un conjunt de tasques relacionades entre si. Un procés defineix tasques concretes que poden diferir en un mètode a un altre, mentre que l'activitat seria la mateixa.

Cada mètode pot donar més o menys importància a cadascuna de les activitats que descrivim a continuació

##### Gestió del projecte

La gestió de projectes és una disciplina general, comuna per a tota mena de projectes de les tecnologies de la informació i comunicació, aquesta inclou tots els processos necessaris per a la direcció, la gestió i l'administració de qualsevol projecte amb independència de quin producte concret s'estigui construint. 

En el cas de projetces de desenvolupament de programari, el mètode general de gestió de projectes d'ha de complementar amb els mètodes, les tècniques i les eines propies dels projectes de desenvolupament de programari.

Les tasques relacionades amb la gestió del projecte són:

- Estudi de viabilitat: Fase prèvia on cal detectar una necessitat en l'organització que l'encarrega i fer un estudi d'alternatives i costos per tal de decidir si el projecte és o no la millor opció per a safisfer les necessitats. 
- Estimació: Cal fer una estimació del cost del projecte i també del temps necessari per a dur-lo a terme i de la relació entre temps i recursos.
- Definir clarament els objectius del projecte, que en determinaran l'èxit o el fracàs. 
- Establir fites que ens permetin dur a terme les activitats de seguiment i control del projecte per tal de verificar-ne la bona marxa (sprints)
- Identificar els riscos que puguin posar en perill l'èxit del projecte.

La gestió del projecte consisteix en equilibrar tres variables:
- L'abast del projecte
- El temps
- El cost

Un canvi en qualsevol d'aquestes tres variables s'ha de compensar modificant una de les altres dues.


##### Identificació i gestió dels requisits

Aquesta activitat implica la comunicació i la col·laboració amb els stakeholders per tal de trobar quins són els requisits del producte que cal desenvolupar.

Segons la guia SWEBOK (2004) els requisits "expressen les necessitats i restriccions que afecten un producte de programari que contribueix a la solució d'un problema del món real".

Els requisits ens serveien per a delimitar quines de les possibles solucions al problema són adequades i quines no.

La identificació i gestió dels requisits està molt relacionada amb l'abast del projecte, ja que els requisits són els que determinen el seu abast. Les principals problemàtiques són les propies de qualsevol activitat de comunicació:

- Diferències respecta a la informació que treballen les diferents parts
	- Els stakeholders tenen informació sobre el producte que els desenvolupadors no
	- Els desenvolupadors tenen informació sobre la tecnologia que els stakeholders no tenen.
- Limitacions del canal utilitzat: Qualsevol canal de ocmunicació imposa limitacions, si la comunicació és escrita es perd el llenguatge no verbal.
- Limitacions del llenguatge utilitzat. El llenguatge natural és propens a l'ambigüitat raó per la qual s'han desenvolupat els llenguatges formals d'especificació.
- Dificultat de definir le millor sistema possible. Aconseguir que els stakeholders comuniquin exactament els requissits del millor sistema possible 

##### Modelització

Fase que inclou la creació de models a desenvolupar, aquesta tècnica és equivalen a la construcció de maquetes o models en altres disciplines.

El llenguatge més utilitzat per a la creació de models de programari és el llenguatge UML (Unified modeling language). Aquest llenguatge no imposa cap mètode de desenvolupament u ha estat adoptat pe rla majoria de mètodes de desenvolupament actuals.

##### Construcció i proves

La construcció inclou l'escriptura de codi font i la realització de les proves necessàries per a garantir l'abscència d'errors en els programes i l'eadequació del producte als requisits. 

Un cop creat el codi, cal crear els arxius executables i posar-los a disposició de l'usuari final.

##### Qualitat 

La gestió de qualitat és una activitat que inclou totes les etapes del desenvolupament, aquesta implica la recol·lecció de mètriques que ens ajudin a determinar si el programari compleix o no els criteris de qualitat marcats i també la documentació formal dels processos de desenvolupament i la verificació del seu compliment.

##### Manteniment

Un cop tancat el projecte de desenvolupament, caldrà engegar noves activitats d'operació i manteniment que quedaran fora de l'àmbit d'aquest.

El manteniment correctiu és aquell que conosisteix en corregir els errors detectats en el programari, i está molt relacionat amb la gestió de la configuració i del canvi, ja que un cop detectat un error caldrá corregir-lo sobre el codi font i generar una nova versió.

El manteniment evolutiu és més semblant a un projecte de desenvolupament ja que consisteix en afegir noves funcionalitats o adaptar-ne les existents.


##### Activitats des del punt de vista del cicle de cida del projecte 

- Tasques d'iniciació
	- Són aquelles relatives a la presa de la decisió sobre si es cinebçarà o no el projecte
	- Com a resultat de les activitats d'inciació obtenim la definició de l'abast del projecte, l'estimació de la durada del projecte i el cost
- Tasques de planificació 
	- Ajuden a organitzar el treball definint quines tasques cal dur a terme i en quin ordre
- Tasques d'execució
	- Són aquelles desitnades a completar la feina requerida per a desenvolupar el producte
- Tasques de seguiment i control
	- Aquelles tasques destinades a observar l'execució del projecte per tal de detectar possibles problemes
- Tasques de tancament
	- Valoració del producte per veure si satisfà les necessitats

#### Rols de l'enginyeria de programari

Dins del desenvolupament del programari es defineixen una série de rols i quines són les tasques de cadascun
##### Cap de projectes

El cap de projectes és la persona responsable d'aconseguir els objectius del projecte.

##### Els experts en el domini

Són les persones coneixedores del sistema que es vol desenvolupar.

##### L'analista funcional

L'analita funcional és el responsable d'unificar les diferents visions del domini en un únic model que sigui clar, concís i consistent.

##### Arquitecte

L'arquitecte és el responsable de definir les linies mestres del disseny del sistema. Entre altres responsabilitats, té la d'escollir la tecnologia adequada per a la implementació del projecte, per a la qual cosa ha de tenir en compe el tipus de producte, els coneixements de l'equip i altres requisits.

##### L'analista tècnic

L'analista técnic s'encarrega del disseny detallat del sistema respectant l'arquitectura definida per l'arquitecte. El destinatari de la seva feina és el programador.

##### Els programadors

Els programadors són els encarrgats d'escriure el codi font a partir de qual s'han de generar els programes.

##### L'expert de qualitat

La seva feina és vetllar per la qualitat del producte desenvolupat

##### L'encarregat del desplegament

És aquegll que, un cop creats i validats els programes, s'encarrega empaqueta els arxius i els envia als entorns adequats per tal de que arribin als usuaris finals.

##### El responsable del producte

Aquest té la visió global del producte que es vol desenvolupar i vetlla pel seu desenvolupament correcte. La seva tasca no és fer un seguiment detallat, sinó aportat una visió global del producte i assegurar-se que el projecte encaixa perfectament amb els objectius i l'estrategia de l'organització.

### Mètodes de desenvolupament de programari

#### Classificació dels mètodes de desenvolupament

Una de les primeres tasques que fa el desenvolupador és triar el mètode que utilitzara per poder dur a terme el projecte, alguns dels factors que és tenen a compte per poder fer la millor tria són:

- risc
- valor de negoci
- durada
- complexitat
- tecnologia utilitzada
- nombre de departaments afectats
- cost

No seguirem el mateix mètode per a un projecte de 3 mesos que per a un de 3 anys, pel risc o la incertesa. 

Podem situar cadascun dels projectes que poguem pensar en un d'aquests quatre grups


|                   | solució coneguda | solució poc coneguda |
| ----------------- | ---------------- | -------------------- |
| Objectiu clar     | 1                | 2                    |
| Objectiu poc clar | 3                | 4                    |

Al grup 1 al saber que i com ho farem necessitarem un mètode poc tolerant al canvi per la seva senzillesa d'aplicar.

Al grup 2 en canvi, necessitarem un mètode que ens permeti canviar les idees a mesura que avança el projecte facilitant el descobriment de la solució fent us de cicles de retroalimentació.

Al grup 3 hi trobem projectes molt peculiars ja que tenim una solució coneguda pero no un problema a solventar.

Al grup 4 trobem projectes de recerca i desenvolupament, en els que hem de ser flexibles tant respectes a la solució tant al problema que busquem com a la solució, ja que, moltes vegades, s'acaba solucionant un problema diferent. 

Al llarg de la materia els classificarem per:

- Els que segueixen el cicle de vida en cascada
- Els mètodes iteratius
- Els àgils

##### Cicle de vida clàssic o en cascada

El cicle de vida clàssic o en cascada és ideal per a projectes del grup 1. És molt senzill d'aplicar i poc tolerant als canvis. La manera d'organitzar el projecte són 5 etapes per a les que passem progressivament que són:

1. **Requisits**: La primera fase que passarem és definir quins són els requisits per tal de dur a terme el projecte. Aquesta etapa és crítica per a l'èxit del projecte, ja que un defecte als requisits es propagarà per a la reta d'etapes.
2. **Ànalisis i disseny**: En la segona fase del projecte definirem com ha de ser el producte internament i externament. 
3. **Implementació**: Escriure codi, manuals i generar el producte executable. En aquesta fase el codi haurà de ser escrit com es detalla a la fase prèvia.
4. **Proves**: Un cop el programa està preparat per a poder ser executat és verificarà que es compleixen els requisits incials i es mostra a l'usuari final.
5. **Maneniment**: Es posa el sistema a disposició de tots els usuaris i es corregeixen els errors que es vagin trobant.

![[Captura de pantalla 2025-10-16 a les 10.08.45.png]]

##### Cicle de vida iteratiu i incremental

El cicle de vida en cascada té l'inconvenient que no ens proporciona cap informació empírica sobre el producte final fins a la darrera etapa. Quan arriba el moment en el que es pot provar el producte per a obtenir informació ja és molt tard per a poder corregir els errors introduits a les primeres fases del desenvolupament.

Per a projectes del grup 2 on necessitem poder anar variant les idees inicials a mesura que avança el projecte utilitzarem el mètode iteratiu. El mètode iteratiu organitza el desenvolupament en cicles iteratius, cada iteració és un miniprojecte autocontigut que augmentarà el cicle anterior. D'aquesta manera podem evitar els problemes del cicle de vida clàssic.

![[Captura de pantalla 2025-10-16 a les 10.29.39.png]]

##### Desenvolupament lean o agile

