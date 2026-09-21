# EXERCICE 3

## COMMITS SELECTIONNEES :

~       COMMANDE UTLISE :
```
bash :
git log --oneline -n 20
```

~       RESULTATS SELECTIONNEES :
.1
```
b50d5072 (HEAD -> main) feat(editmode): overlay respecte la profondeur (X-ray), flushing de selection et aretes a couleur interpolee
```
.2
```
718f8d0b perf(nkcontainers): NkVector copy-ctor + operator= via memcpy AVX2 pour types trivialement copiables (etait PushBack element-par-element) - footgun moteur, valait 35% du decodage HEVC ; comportement inchange (suite codec bit-exacte identique)
```

.3
```
94f0c479 refactor(noge): purge STL residuelle des 5 en-tetes spec (regle zero-STL)
```
## CONTENU DE CHAQUE COMMIT :

1.
~       COMMANDE UTLISE :
```
bash :
git show --stat b50d5072
```

~       RESULTATS :
 

```
commit b50d5072bdeb7a96e3bc583a2f651877fe87adc1 (HEAD -> main)
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Mon Jul 27 21:24:24 2026 +0100

    feat(editmode): overlay respecte la profondeur (X-ray), flushing de selection et aretes a couleur interpolee
    
    OVERLAY AVEC DEPTH (bug 'wireframe selon l'angle') :
    - Les marqueurs de sommets / centres de face etaient dessines en no-depth INCONDITIONNEL
      (DrawDebugTriangle overlay=true en dur) -> ils suivent desormais st->editXray, comme le
      remplissage de face. X-ray OFF = overlay occlus par la geometrie ; X-ray ON = no-depth.
      Le GIZMO reste no-depth dans tous les cas (chemin separe, volontaire).
    - Le lift radial de la cage passe de rad*0.006f a rad*0.0035f : assez pour eviter le
      z-fighting (teste : 0.0015f fait revenir les pointilles), assez peu pour ne plus deborder
      devant une geometrie voisine (cas de la colonne fine signale par l'auteur).
      NOTE : reglage visuel empirique ; le correctif de fond serait un depth-bias cote pipeline
      de lignes plutot qu'un decalage geometrique.
    
    FLUSHING DE SELECTION (facon Blender) : les SOMMETS sont la source de verite ; une arete est
    selectionnee si ses 2 extremites le sont, une face si tous ses sommets le sont. Recalcule
    apres chaque modification (clic, Shift+clic, deselection, rectangle, lasso, cercle, boucle)
    et apres chaque operation d'edition, sur l'identite topologique SOUDEE.
    
    ARETES A COULEUR INTERPOLEE ('semi-selectionne' de Blender) : le batch de lignes portait
    deja une couleur PAR SOMMET (pos3+rgba4) -> le GPU interpole nativement, cout nul, un seul
    draw call, aucun decoupage en segments necessaire. Chaque extremite recoit SA couleur :
    un sommet selectionne teinte ses aretes incidentes en degrade (orange pres du sommet,
    noir a l'autre bout) ; sommet actif = blanc. Tri en 2 passes ajuste : les aretes ayant AU
    MOINS une extremite selectionnee passent en 2e passe pour gagner le z-fight.

 Applications/Sandbox/src/Demo/Demo3D.cpp | 41 +++++++++++++++++++++++++-------
 1 file changed, 33 insertions(+), 8 deletions(-)
```

.2
~       COMMANDE UTLISE :
```
bash :
 git show --stat 718f8d0b
```

~       RESULTATS :
 

```
commit 718f8d0bf3c07937a65ab72cab4aa85a75a27f7f                                                                                      
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Sun Jul 26 20:21:35 2026 +0100

    perf(nkcontainers): NkVector copy-ctor + operator= via memcpy AVX2 pour types trivialement copiables (etait PushBack element-par-element) - footgun moteur, valait 35% du decodage HEVC ; comportement inchange (suite codec bit-exacte identique)

 .../src/NKContainers/Sequential/NkVector.h         | 28 ++++++++++++++++++----
 1 file changed, 24 insertions(+), 4 deletions(-)
```
 
 .3

        COMMANDE UTLISE :
```
bash :
git show --stat 94f0c479
```

~       RESULTATS :
 

```
commit 94f0c479b3b5cb5e86bc945c0c419a2db7a2f006
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Sun Jul 26 19:10:27 2026 +0100

    refactor(noge): purge STL residuelle des 5 en-tetes spec (regle zero-STL)
    
    NkScriptPython/CSharp, NkBlueprint/HotReload, NkFacialRig : suppression de tout std::
    (vector/string/function/unique_ptr/chrono/cstring/cstdio) -> NkVector/NkString/NkFunction/
    NkUniquePtr(NKMemory)/NKTime/NkStrNCpy. Lecture de script Python : NkFile::ReadAllText +
    PyRun_String (plus de fopen/FILE* libc). Types FFI Python/Mono (PyObject*/MonoObject*)
    conserves (interop C legitime, pas de la STL). Verifie : 0 std:: residuel, 5/5 -fsyntax-only,
    build Noge 38/38 SUCCESS.

 .../src/Noge/ECS/Scripting/CSharp/NkScriptCSharp.h |  2 +-
 .../src/Noge/ECS/Scripting/Python/NkScriptPython.h | 36 +++++++++++-----------
 .../Noge/src/Noge/ECS/VisualScript/NkBlueprint.h   |  2 +-
 .../Noge/ECS/VisualScript/NkBlueprintHotReload.h   |  4 +--
 Engine/Noge/src/Noge/Facial/NkFacialRig.h          |  3 +-
 5 files changed, 24 insertions(+), 23 deletions(-)
```

### REPONSES A L'EXERCICE :



## Commit 1 — b50d5072

Message :
```
    feat(editmode): overlay respecte la profondeur (X-ray), flushing de selection et aretes a couleur interpolee
    
    OVERLAY AVEC DEPTH (bug 'wireframe selon l'angle') :
    - Les marqueurs de sommets / centres de face etaient dessines en no-depth INCONDITIONNEL
      (DrawDebugTriangle overlay=true en dur) -> ils suivent desormais st->editXray, comme le
      remplissage de face. X-ray OFF = overlay occlus par la geometrie ; X-ray ON = no-depth.
      Le GIZMO reste no-depth dans tous les cas (chemin separe, volontaire).
    - Le lift radial de la cage passe de rad*0.006f a rad*0.0035f : assez pour eviter le
      z-fighting (teste : 0.0015f fait revenir les pointilles), assez peu pour ne plus deborder
      devant une geometrie voisine (cas de la colonne fine signale par l'auteur).
      NOTE : reglage visuel empirique ; le correctif de fond serait un depth-bias cote pipeline
      de lignes plutot qu'un decalage geometrique.
    
    FLUSHING DE SELECTION (facon Blender) : les SOMMETS sont la source de verite ; une arete est
    selectionnee si ses 2 extremites le sont, une face si tous ses sommets le sont. Recalcule
    apres chaque modification (clic, Shift+clic, deselection, rectangle, lasso, cercle, boucle)
    et apres chaque operation d'edition, sur l'identite topologique SOUDEE.
    
    ARETES A COULEUR INTERPOLEE ('semi-selectionne' de Blender) : le batch de lignes portait
    deja une couleur PAR SOMMET (pos3+rgba4) -> le GPU interpole nativement, cout nul, un seul
    draw call, aucun decoupage en segments necessaire. Chaque extremite recoit SA couleur :
    un sommet selectionne teinte ses aretes incidentes en degrade (orange pres du sommet,
    noir a l'autre bout) ; sommet actif = blanc. Tri en 2 passes ajuste : les aretes ayant AU
    MOINS une extremite selectionnee passent en 2e passe pour gagner le z-fight.
```
### Dit-il ce qu'il fait ?

Oui. Le message indique que le commit modifie le comportement de
l'overlay avec la profondeur/X-ray, la gestion de la sélection et la
couleur des arêtes.

Le contenu du commit confirme ces trois changements dans
Applications/Sandbox/src/Demo/Demo3D.cpp.

### Dit-il pourquoi ?

Partiellement. Le corps du message explique notamment les problèmes
de profondeur, de z-fighting et le comportement de sélection recherché.
Cependant, le sujet lui-même décrit surtout les changements et ne donne
pas vraiment leur raison.

### Porte-t-il un seul sujet ?

Non. Le commit regroupe trois changements :
- le respect de la profondeur par l'overlay ;
- le recalcul de la sélection ;
- la couleur interpolée des arêtes.



---

## Commit 2 — 718f8d0b

Message :
```
  perf(nkcontainers): NkVector copy-ctor + operator= via memcpy AVX2 pour types trivialement copiables (etait PushBack element-par-element) - footgun moteur, valait 35% du decodage HEVC ; comportement inchange (suite codec bit-exacte identique)
```

### Dit-il ce qu'il fait ?

Oui. Le message indique précisément que le constructeur de copie et
l'opérateur d'affectation de NkVector utilisent memcpy avec AVX2 pour
les types trivialement copiables, à la place du traitement élément par
élément.

ici Le commit ne modifie qu'un fichier : NkVector.h.

### Dit-il pourquoi ?

Oui. Le message indique que cette opération représentait 35 % du
décodage HEVC et précise que le comportement reste inchangé.


### Porte-t-il un seul sujet ?

Oui,. Les différentes précisions du message concernent
toutes l'optimisation des opérations de copie de NkVector.

---

## Commit 3 — 94f0c479

Message :
```
 refactor(noge): purge STL residuelle des 5 en-tetes spec (regle zero-STL)
```

### Dit-il ce qu'il fait ?

Oui. Le message indique que les dépendances STL restantes sont
supprimées de cinq en-têtes du projet Noge.

Le corps précise les remplacements effectués et les cinq fichiers
concernés.

### Dit-il pourquoi ?

Oui. La raison est la règle « zero-STL ». Le corps indique également
les vérifications effectuées après le changement : absence de std::
résiduel, vérification syntaxique des cinq fichiers et réussite du
build.

### Porte-t-il un seul sujet ?

Oui, Même si cinq fichiers sont modifiés, ils sont tous
concernés par le même objectif qui est supprimer la STL résiduelle selon la
règle zero-STL.

---

# Message le plus faible

Parmi ces trois messages, je trouve que celui du commit b50d5072 est
le moins adapté aux règles du cours.

Il décrit bien les changements, mais il regroupe trois sujets différents
dans un même commit : l'overlay avec la profondeur, la gestion de la
sélection et la couleur interpolée des arêtes.

## Réécriture proposée

### Sujet

feat(editmode): overlay respecte la profondeur (X-ray).

### Corps

OVERLAY AVEC DEPTH (bug 'wireframe selon l'angle') :
    - Les marqueurs de sommets / centres de face etaient dessines en no-depth INCONDITIONNEL
      (DrawDebugTriangle overlay=true en dur) -> ils suivent desormais st->editXray, comme le
      remplissage de face. X-ray OFF = overlay occlus par la geometrie ; X-ray ON = no-depth.
      Le GIZMO reste no-depth dans tous les cas (chemin separe, volontaire).