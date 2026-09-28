# Exercice 3 

Le programme proposait trois méthodes :
```
le bouton de fermeture de la fenêtre ;
le raccourci du gestionnaire de fenêtres ;
la touche personnelle du programme (Échap).
```
Test réalisé
Le programme a été lancé avec succès et la fenêtre s’est ouverte.
J’ai testé la touche personnelle du programme avec Échap.
La sortie obtenue dans le terminal est :

```
[TOUCHE] Echap pressee.
[TOUCHE] Demande de fermeture recue.
[TOUCHE] Attente de l'evenement NK_WINDOW_CLOSE.
[FERMETURE] Evenement NK_WINDOW_CLOSE recu.
[FERMETURE] Appel de window.Close().
[FERMETURE] Fenetre fermee proprement.

========================================
FIN D'EXECUTION
========================================

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (7.01s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
# Observation
Le test avec Échap montre que la touche ne ferme pas directement la fenêtre.
Le programme détecte d’abord la touche :
```
[TOUCHE] Echap pressee.
```
puis indique qu’il attend l’événement de fermeture :
```
[TOUCHE] Attente de l'evenement NK_WINDOW_CLOSE.
```
L’événement de fermeture est ensuite reçu :
```
[FERMETURE] Evenement NK_WINDOW_CLOSE recu.
```
et c’est à ce moment que window.Close() est appelé :
```
[FERMETURE] Appel de window.Close().
```
Enfin, le programme confirme :
```
[FERMETURE] Fenetre fermee proprement.
```
Limite du test
Dans cette session, seul le chemin avec la touche Échap est documenté par une sortie de terminal fournie.
Je n’ai pas de sortie terminal correspondant aux deux autres méthodes :
bouton de fermeture du système ;
raccourci du gestionnaire de fenêtres.
Je ne les présente donc pas comme des tests effectivement réalisés.😓

# Conclusion
Le test réalisé confirme que la touche Échap passe bien par l’événement NK_WINDOW_CLOSE avant l’appel à window.Close().
Le programme se termine normalement après la fermeture.