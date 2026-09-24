# EXERCICE 3:


## PROGRAMME ATTENDU :
```
#include "NKWindow\NKWindow.h"
#include "NKWindow\NKMain.h" /* fournis le point d'entree natif */

int nkmain(const NkEntryState &state) {

    // configuration de la fenetre : titre, largeur et hauteur.
    NKWindowconfig cfg;
    cfg.title = "MA PREMIERE FENETRE";
    cfg.width = 800;
    cfg.height = 800;

    // creation de la fenetre.
    NKWindow window(cfg);
    if(!window.IsOpen) { // Dans le guide la forme ici est window.Create(cfg) et non Window.IsOpen()🥲
        logger.Error(" DE CREATION DE LA FENETRE"); /* en cas d'echec on signale l'erreur dans le log */
        return -1;
    }

    // boucle principal de la fenetre
    while(window.IsOpen()) { /* attente des evenements*/ }
    return 0;
}
```
1. CE PROGRAMME COMPORTE 22 LIGNES.

2. LES LIGNES DU CHAPITRE :
```
 . #include "NKWindow\NKWindow.h" : c'est l'entete qui donne acces aux elements necessaires a la creation et au controle de la fenetre, notamment NKWindow et NKWindowCOnfig.
```
```
 . #include "NKWindow\NKMain.h" NKentseu fournit le point d'entree natif adaptee a la plateforme et l'application ecrit nkmain().
```
```
 . int nkmain(const NkEntryState &state) : c'est le point d'entree de l'application NKentseu
```
```
. NKWindowconfig cfg; : Definit la fenetre, cfg.title = "MA PREMIERE FENETRE"; cfg.weight = 800; cfg.height = 800; definissent respectivement le titre de la fenetre, sa largeur et sa hauteur.
```
```
.  NKWindow window(cfg); : creation de la fenetre
```
```
. if(!window.IsOpen) : apres la creation, on verifie que la fenetre soit ouverte.
```
```
. logger.Error(" DE CREATION DE LA FENETRE"); /* en cas d'echec on signale l'erreur dans le log */ : message en cas d'echec d'ouverture de la fenetre
```
```
.  while(window.IsOpen()) { /* attente des evenements*/ } : tant que la fenetre est ouverte, ll'application reste dans sa boucle.
```

## DETAILS AYANT ATTIRE MON ATTENTION :
 dans le guide, pour creer une fenetre la forme utilise apres NKWindowConfig... est :

 NKWindow window;

if (!window.Create(cfg)) {...}

ce aui differe du chapitre fournis ici.
