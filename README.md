*---------------------------------*
|  The shooter                    |
|  Sistemes Operatius Avançats    |
|  -Author:Alejandro Moñux Bernal |
*---------------------------------*

*--------------------------*
|Instruccions de compilació|
*--------------------------*
A la propia carpeta root del projecte hi ha un makefile.
Hi ha suficient en utilitzar la comanda "make" dins d'aquest directori per a compilar el codi i crear l'executable "main".
Els fitxers per a testejar l'execució es troben a la carpeta "files" i els fitxers del codi son a:
  -main.c:                    Carpeta root.
  -Fitxers relatius a FAT16:  Carpeta FAT16.
  -Fitxers relatius a EXT2:   Carpeta ext2.
  -Fitxers d'eines a part:    Carpeta tools.

*-----------------------------------*
|Explicació dels sistemes de fitxers|
*-----------------------------------*

/-----------------------------------\
|             FAT16                 |
\-----------------------------------/
FAT16 es un sistema de fitxers organitzat en clusters i sectors, es a dir:
  -Clusters: Colleció de informació sequencial, organitzada de forma contigua en disc. Serveixen per adreçar la informació i sovint estàn subdividits en sectors.
  -Sectors:Mesura més petita de dades dins d'un disc. Comunment un fitxer ocupa X sectors i en aquest cas trobem aquests sectors agrupats en Clusters.

Aquest format presenta un boot sector (o BPB) que es el priemr sector del volum. En aquest volum es troben un munt de dades sobre el volum, com els sectors per cluster, el nom del volum, nombre de entrades màximes per directori, nombre de FATs, de sectors... En aquest sector, en genral, trobarem gran part d'allò que necessitarem per navegar.

Per accedir al sector del directori, tenim que saltar els sectors reservats i el nombre de FATS per sectors per fat. Si això ho multipliquem per els bytes per sector, tindrem el bytes d'accès. En canvi, per els subdirectoris tindrem que accedir al cluster del directori en sí, sumant-li lo anterior més les entrades de root ja que el ordre es sequencial (BootSector, ReservedSectors, RootEntries...).
/-----------------------------------\
|             EXT2                  |
\-----------------------------------/
A diferència de FAT16, EXT2 presenta un sistema bastant més organitzat. En aquest cas partim de blocks i block groups, amb els que adreçem les diferents parts del volum. A això afegim els inodes i com un directori poseeix inode bitmaps i inode tables.
  -Blocks: La unitat bàsica de direccionament, agrupada posteriorment en block groups.
  -Group Blocks: Grups de blocs que eviten la fragmentacio. Els primers sovint s'utilitzen per bitmaps i taulas de informació sobre els Grups.
  -Inode (index node): Tot objecte es representat per un. Cada inode apunta a una taula amb la metadata del objecte i els blocks on anar per llegir-ho. Hi ha una inode table per block group i dins d'aquesta podem veure els blocks del grup. S'agrupen també en grups, ja que poden haber-hi diferents inodes dins un grup de blocks.
  -Superblock: Fa la mateixa funció que el BPB del FAT. En aquest cas la trobem en un offset de 1024 bytes.

En aquest cas, per accedir el directori base hem de saltar el offset base, la inode table base i afegir el offset al first inode.

En cas d'accedir a un subdirectori, hem de fer el salt no al first Inode, si no a el inode del directori en questió. Per a fer això hem de llegir de la entrada del directori i tenir en compte el nombre de inodes que hi ha a cada grup.

*-----------------------------------*
|Explicació de la pràctica          |
*-----------------------------------*

/-----------------------------------\
|            Requeriments           |
\-----------------------------------/

Aquesta pràctica es pot resumir en unes poques funcionalitats.
Principalment, hem de verificar que el arxiu sigui FAT16 o EXT2. Un cop sabem això, hem de seguint una de les funionalitats a implementar:
  -/info : Aquesta funcionalitat mostrarà certa informació del volum en questiò
  -/find : Passant el volum i un nom de arxiu a buscar, hem de trobar en root i en subdirectoris del volum el arxiu i mostrar també el seu size.
  -/delete: Passant el volum i un nom de arxiu, buscarà i eliminarà el arxiu. En aquest cas això s'ha implementat en conjunt amb el find.

/-----------------------------------\
|            Disseny                |
\-----------------------------------/

La pràctica s'ha dividit en tres parts: el FAT i el EXT, amb branques al git i carpetes que separen i aïllen aquestes des seccions, i una secció d'eines generals menys important.
De la mateixa manera, dins de la secció de FAT i EXT està tot dividit entre tres subseccions:
  -seccio_info:   Aquesta subsecció té tot allò necessari per la obtenció de informació de diferents parts del sistema d'arxius.
  -seccio_find:   Aquesta subsecció té les eines necessaries per buscar arxius i les funcionalitats de find.
  -seccio_delete: Aquesta subsecció té les eines necessaries per eliminar arxius i les funcionalitats de delete.

/-----------------------------------\
|      Estructures de dades         |
\-----------------------------------/
DirectoryEntryExt (DEntryExt) i DirectoryEntry(DEntry) son estructures utilitzades a l'hora de esborrar els arxius. En aquestes es guarden les dades de la entrada de directori.
Amb aquestes entrades de directori llegim i dresprès escribim la informació dins l'arxiu de nou, utilitzant-los com a contenidors per fer mès cómode aquesta operació.

_LongFileName(LFN), es una estructura utilitzada per a guardar la informació de una entrada de nom llarg al FAT. Certs arxius necessiten això per a poder buscar-los, de manera que vaig necessitar això per poder localitzar la informació del nom el arxiu en un mateix lloc.

/-----------------------------------\
|      Proves realitzades           |
\-----------------------------------/
Les proves que han sigut realitzades es poden dividir en dues parts; aquella que va de la Fase 1 a la 3 i la Fase Final.
  -De la fase 1 a la 3:
    En aquesta part, les proves s'han realitzant mitjançant l'execució i comparació de valors llegits/calculats amb l'eina hexdump.
    Ademés d'això, en la fase 2 i la 3 també vaig fer us de una máquina virtual de Linux per muntar els arxius i verificar allò que tenia que llegir i què hi havia a on.
  -La Fase Final:
    En la fase final del que més he fet ús ha sigut de la màquina virtual ja anomenada. L'he utilitzat per muntar els directoris cada vegada que eliminava arxius i així poder anar comprovant que tot s'estiguès eliminant correctament.

/-----------------------------------\
|      Problemes observats          |
\-----------------------------------/
Problemes amb el EXT2:
El problema principal del EXT2 ha sigut realitzar la operació per moure's dins del volum. Amb bastants problemes, es va poder solucionar mitjançant l'anàlisi de els recurs dels que disposava i del output de la comanda hexdump per saber la localització en bytes d'allò que buscava llegir.

Un altre problema va ser a l'hora de borrar el arxiu. Donat que en EXT cada entrada no té una llargada fixe, alguns noms van quedar corruptes o entrades desapareixien. Això venia degut a la diferència de rec_len entre diferents entrades i a que, degut a això, en ocasions hi habia entrades sent sobre-escrites. Vigilant aquesta diferència i amb una variable per aplicarla a la re-escriptura dels directoris, es va poder solucionar això.

Problemes amb el FAT16:
Amb el FAT16 va haber-hi un problema i es que durant la Fase 2 no hi havia fitxers amb long file name i durant la fase 3 sí. Així doncs, es va tenir que canviar la forma en que es llegien les noms durant la fase 3 per a arreglar aquest problema. Un cop es va ficar la lectura del filename, ja es trobaven certs fitxers i no va haver-hi molt més problema.
/-----------------------------------\
|      Estimació temporal           |
\-----------------------------------/

Gran cantitat de treball ha sigut fet durant les hores de classe, encara que fora d'aquestes també s'ha realitzar bastant treball, especialment durant les dues últimes fases.
Aproximadament, el cost temporal de cada fase es:

Fase 1: 8h

Fase 2: 12h

Fase 3: 12h

Fase 4: 12h

Cost temporal total: 44h

*-----------------------------------*
|Explicació i valoració del GIT     |
*-----------------------------------*
La estructura del GIT per a la práctica es la següent:

  -master:  Branca que recollirà els commits mergejats de dev i de la que sortirà tant dev com les fases de les que es fagi una release.
  -dev:     Branca de la que sortiràn EXT2 i FAT16. Serà una branca que les recollirà un cop les noves funcionalitats estiguin estables.
  -FAT16:   Branca de desenvolupament de les funcionalitats de FAT16. No té per què ser estable.
  -EXT2:    Branca de desenvolupament de les funcionalitats de FAT16. No té per què ser estable.
  -Fase_X:  Branca de release de la fase en questió. Recull dins el readme i els fitxers de test, ademés del codi corresponent.

master_________________________________________________________________
              dev\______________________________/      Fase_X\____
                    \   EXT2\_____________/  /
                FAT16\______________________/

Aquest tipus d'organització resulta en un projecte més estable, on les parts problemàtiques es queden localitzades en les seccions específiques de cada fase. De la mateixa manera, en tenir les releases en branques separades, aïllem aquests punts de possibles problemes.        

*-----------------------------------*
|          Conclusions              |
*-----------------------------------*

Cada sistema de fitxers comporta les seves peculiaritats, encara que degut a la seva estructura EXT2 es més escalable i a la llarga permet guardar arxius de més tamany donat que dins un inode podem guardar diversos blocks i un grup poseeis diversos inodes. La limitació del fat dels clusters i els sectors fa que ens trobem més limitats.

Amb això en ment, trobo que resulta més fàcil d'entendre el FAT i que navegar per un fat i modificar el seu contingut es més simple que un ext, que requereix de moltes més operacions i valors a tenir en compte a cada moment.

Depenent del ús que estem buscant, fa millor prendre un o l'altre. Potser necessitem més espai màxim d'arxiu o potser necessitem una gestió més rápida d'arxius. Com sempre, hem de plantejar-nos les opcions abans d'escollir.
