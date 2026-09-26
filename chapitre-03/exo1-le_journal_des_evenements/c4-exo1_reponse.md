# Exercice 1

1. Le programme utilise NkEvents().PollEvent() pour récupérer les événements.

## Événements observés
Lors du lancement et de l’utilisation de la fenêtre, plusieurs événements ont été reçus.
Création et affichage de la fenêtre
Les premiers événements observés sont :
```
NK_WINDOW_CREATE
NK_WINDOW_FOCUS_GAINED
NK_WINDOW_FOCUS_GAINED
NK_WINDOW_SHOWN
NK_WINDOW_RESTORE
NK_WINDOW_MOVE
NK_WINDOW_PAINT
NK_WINDOW_RESIZE
NK_WINDOW_MOVE
```
Ils correspondent principalement à la création, l’affichage, le déplacement et le redimensionnement de la fenêtre.
## Déplacement de la souris
En déplaçant la souris, les événements suivants ont été observés :
```
NK_MOUSE_ENTER
NK_MOUSE_MOVE
NK_MOUSE_MOVE
```
Cela montre que le déplacement de la souris produit plusieurs événements dans le journal.
## Utilisation du clavier
Lors d’une utilisation du clavier, les événements suivants ont été observés :
```
NK_KEY_PRESSED
NK_KEY_RELEASED
```
Un autre NK_KEY_PRESSED a également été observé plus tard.

## Perte du focus et fermeture
À la fin de l’exécution, les événements suivants ont été observés :
```
NK_WINDOW_FOCUS_LOST
NK_WINDOW_FOCUS_LOST
NK_WINDOW_DESTROY
```
Le dernier événement correspond à la destruction de la fenêtre.
## Comptage pendant une seconde
Le programme compte les événements reçus pendant une période d’une seconde.
Lors de la première mesure, le terminal indique :
```
Nombre d'evenements pendant 1 seconde : 12
```
Une deuxième mesure a ensuite donné :
```
Nombre d'evenements pendant 1 seconde : 2
```
Les deux mesures sont différentes car le nombre d’événements dépend des actions effectuées pendant la seconde : déplacement de la souris, utilisation du clavier, redimensionnement ou autres interactions.
## Observation du résultat
Le test montre qu’une utilisation normale de la fenêtre peut produire plusieurs événements en très peu de temps.
Dans cette exécution, les événements de fenêtre et de souris ont été particulièrement visibles au début, puis les événements clavier sont apparus lors de la saisie.
Le programme termine normalement :
FIN D'EXECUTION — termine normalement (2.18s)

## resultat du terminale :
```
Evenement : 32  - famille (code) :  NK_WINDOW_CREATE 

 Evenement : 32  - famille (code) :  NK_WINDOW_FOCUS_GAINED 

 Evenement : 32  - famille (code) :  NK_WINDOW_FOCUS_GAINED 

 Evenement : 32  - famille (code) :  NK_WINDOW_SHOWN 

 Evenement : 32  - famille (code) :  NK_WINDOW_RESTORE 

 Evenement : 32  - famille (code) :  NK_WINDOW_MOVE 

 Evenement : 32  - famille (code) :  NK_WINDOW_PAINT 

 Evenement : 32  - famille (code) :  NK_WINDOW_RESIZE 

 Evenement : 32  - famille (code) :  NK_WINDOW_MOVE 

 Evenement : 20  - famille (code) :  NK_MOUSE_ENTER 

 Evenement : 20  - famille (code) :  NK_MOUSE_MOVE 

 Evenement : 20  - famille (code) :  NK_MOUSE_MOVE 

 Nombre d'evenements pendant 1 seconde : 12
 Evenement : 12  - famille (code) :  NK_KEY_PRESSED 

 Evenement : 12  - famille (code) :  NK_KEY_RELEASED 

 Nombre d'evenements pendant 1 seconde : 2
 Evenement : 12  - famille (code) :  NK_KEY_PRESSED 

 Evenement : 32  - famille (code) :  NK_WINDOW_FOCUS_LOST 

 Evenement : 32  - famille (code) :  NK_WINDOW_FOCUS_LOST 

 Evenement : 32  - famille (code) :  NK_WINDOW_DESTROY 

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (2.18s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

## Conclusion
L’exercice a permis de mettre en place un journal des événements reçus par la fenêtre et d’observer leur type.
Les tests réalisés ont notamment permis d’observer des événements de fenêtre (NK_WINDOW_*), de souris (NK_MOUSE_*) et de clavier (NK_KEY_*).
Pendant une seconde d’utilisation, le programme a compté 12 événements lors de la première mesure, puis 2 événements lors de la deuxième mesure.